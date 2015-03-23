#include "packetparser.h"
#include <QDebug>
#include <QString>
#include <vector2d.h>

PacketParser::PacketParser()
{
}

void PacketParser::handleWorldPacket(ssl_world_packet p)
{
//    p.PrintDebugString();
    if(p.has_blue_team()) {
        for(int i=0; i<p.blue_team().robots_size(); i++)
        {
            ssl_world_packet_Robot* robot = p.mutable_blue_team()->mutable_robots(i);
            RobotState robot_state(SSL::Blue, robot->id());
            robot_state.position = Vector3D(robot->position().x(), robot->position().y(), robot->position().teta());
            robot_state.velocity = Vector3D(robot->velocity().x(), robot->velocity().y(), robot->velocity().teta());

            emit newRobotState(robot_state);
        }
    }

    if(p.has_yellow_team()) {
        for(int i=0; i<p.yellow_team().robots_size(); i++)
        {
            ssl_world_packet_Robot* robot = p.mutable_yellow_team()->mutable_robots(i);
            RobotState robot_state(SSL::Yellow, robot->id());
            robot_state.position = Vector3D(robot->position().x(), robot->position().y(), robot->position().teta());
            robot_state.velocity = Vector3D(robot->velocity().x(), robot->velocity().y(), robot->velocity().teta());

            emit newRobotState(robot_state);
        }
    }

    for(int i=0; i<p.field_balls_size(); i++) {
        ssl_world_packet_Ball* ball = p.mutable_field_balls(i);
        BallState ball_state(i);
        qDebug()<<"world packet : ball pos : "<<ball->position().x() << ball->position().y();
        ball_state.position = Vector2D(ball->position().x(), ball->position().y());
        ball_state.velocity = Vector2D(ball->velocity().x(), ball->velocity().y());
        ball_state.acceleration = Vector2D(ball->acceleration().x(), ball->acceleration().y());
        ball_state.rawVelocity  = Vector2D(ball->velocity_raw().x(), ball->velocity_raw().y());
        ball_state.displacement = Vector2D(ball->displacement().x(), ball->displacement().y());

        emit newBallState(ball_state);
    }

    if(p.has_referee_state()) {
        qDebug() << "Referee State: " << p.referee_state().c_str();
        emit newRefereeState(QString(p.referee_state().c_str()));
    }

}

void PacketParser::handleDecisionPacket(ssl_decision_packet p)
{
    if(p.has_comment()) {
        qDebug() << p.comment().c_str();
    }
    if(p.has_our_color() && p.has_our_side()) {
        emit ourColorAndSide((p.our_color()==ssl_decision_packet_Color_blue)? SSL::Blue:SSL::Yellow,
                             (p.our_side()==ssl_decision_packet_Side_left)? SSL::Left:SSL::Right);
    }
    if(p.has_strategy_name()) {
        QString strategy_name = QString(p.strategy_name().c_str());
        QMap<int, QString> robot_role_map;
        for(uint i=0; i<p.robot_roles_size(); i++) {
            ssl_decision_packet_Robot_Role* robot_role = p.mutable_robot_roles(i);
            QString robot_role_name = QString(robot_role->current_role().c_str());
            while (robot_role_name.length() > 0) {
                if(robot_role_name.at(0).isNumber()) {
                    robot_role_name.remove(0, 1);
                }
                else
                    break;
            }
            if(!robot_role->mutable_current_skill()->empty())
            robot_role_map.insert(robot_role->robot_id(), robot_role_name
                                  + " [" +robot_role->mutable_current_skill()->at(0) + "]");
        }
        emit currentStrategy(strategy_name, robot_role_map);
    }
}

void PacketParser::handleAnalyzerPacket(ssl_analyzer_packet p)
{
    if(p.has_comment())
    {
        qDebug() << p.comment().c_str();
    }
    if(p.has_is_game_running())
    {
        emit gameRunning(p.is_game_running());
    }
    if(p.has_nearest_blue_id() && p.has_nearest_yellow_id() && p.has_possessor_team() && p.has_nearest_can_kick())
    {
        qDebug() << "nearest blue ID: " << p.nearest_blue_id() <<" nearest yellow ID: "<<p.nearest_yellow_id()
                 << "total :" << p.possessor_team();
        if(p.possessor_team() == ssl_analyzer_packet_Color_blue)
            emit newNearestRobotToBall(p.nearest_blue_id(), p.nearest_yellow_id(), SSL::Blue, p.nearest_can_kick());
        else if(p.possessor_team() == ssl_analyzer_packet_Color_yellow)
            emit newNearestRobotToBall(p.nearest_blue_id(), p.nearest_yellow_id(), SSL::Yellow, p.nearest_can_kick());
        else if(p.possessor_team() == ssl_analyzer_packet_Color_none)
            emit newNearestRobotToBall(p.nearest_blue_id(), p.nearest_yellow_id(), SSL::None, p.nearest_can_kick());
    }

    for(int i=0; i<p.intersects_size(); i++) {
        ssl_analyzer_packet_RobotIntersectTime* intersect_i =  p.mutable_intersects(i);
        int id_ = intersect_i->id();
        SSL::Color color_ = (intersect_i->color() == ssl_analyzer_packet_Color_blue)? SSL::Blue:SSL::Yellow;
        float time_ = intersect_i->time();
        Vector2D point_(intersect_i->intersect_x(), intersect_i->intersect_y());
        RobotState state_(color_, id_);
        state_.position = point_.to3D();
        emit newIntersectPoint(time_, state_);
    }
}

void PacketParser::handlePlannerPacket(ssl_planner_packet p)
{
    if(p.has_comment())  {
        qDebug() << p.comment().c_str();
    }
    for(int i=0; i< p.plans_size(); i++)
    {
        QVector<RobotState> plan;
        int robotID = p.plans(i).id();
        RobotState state;
        state.ID = robotID;
        state.position = Vector3D(p.plans(i).initstate().x(), p.plans(i).initstate().y(), p.plans(i).initstate().teta());
        plan.append(state);

        for(int t=0; t< p.plans(i).pathstate_size(); t++)
        {
            state.position = Vector3D(p.plans(i).pathstate(t).x(), p.plans(i).pathstate(t).y(), p.plans(i).pathstate(t).teta());        
            plan.append(state);
        }

        RobotState goal_state;
        goal_state.position = Vector3D(p.plans(i).goalstate().x(), p.plans(i).goalstate().y(), p.plans(i).goalstate().teta());
        plan.append(goal_state);
        QVector3D desired_vel(p.plans(i).desiredvel().x(), p.plans(i).desiredvel().y(), p.plans(i).desiredvel().teta());
        QVector3D applied_vel(p.plans(i).appliedvel().x(), p.plans(i).appliedvel().y(), p.plans(i).appliedvel().teta());
        emit newPlan(robotID, plan, desired_vel, applied_vel);
        emit newRobotVelocity(robotID, desired_vel, applied_vel);        
    }

}

