#include "guihandler.h"
//#include "boost/shared_ptr.hpp"
#include "paramater-manager/parametermanager.h"
#include "../definition/SSLRobot.h"
#include "../definition/sslagent.h"
#include "../definition/SSLBall.h"
#include "../definition/sslstrategy.h"
#include "../soccer/roles/sslrole.h"

GUIHandler* GUIHandler::instance = NULL;
using namespace boost;
GUIHandler::GUIHandler()
{    
    this->openSocket();
}

GUIHandler *GUIHandler::getInstance()
{
    if(instance == NULL)
        instance = new GUIHandler();
    return instance;
}

bool GUIHandler::openSocket()
{
    ParameterManager* pm = ParameterManager::getInstance();
    openSocket(pm->get<int>("network.VISUALIZER_PORT"),pm->get<string>("network.VISUALIZER_IP"));

}

bool GUIHandler::openSocket(int port, string address)
{
    this->close();
    if(!this->open(port, true, true)) {
        cerr << "Unable to open UDP network port: "<< port << endl;
        return false;
    }

    Net::Address multiaddr, interface;
    multiaddr.setHost(address.c_str(), port);
    interface.setAny();   

    if(!this->addMulticast(multiaddr, interface))
    {
        cerr << "Unable to setup UDP multicast." << endl ;
    }else
    {
        cout << "Visualizer UDP network successfully configured. Multicast address= " << port << endl;
    }
    return true;
}

void GUIHandler::check()
{
//    shared_ptr<ssl_visualizer_packet> packet(generateVisualizerPacket());
    ssl_visualizer_packet* packet = generateVisualizerPacket();

    sendPacket(*packet);
    if(packet != NULL)
        delete packet;
}

ssl_visualizer_packet *GUIHandler::generateVisualizerPacket()
{
    ssl_visualizer_packet* visualizer_packet = new ssl_visualizer_packet();
    ssl_world_packet *w_p = visualizer_packet->mutable_world_data();
    generateWorldPacket(w_p);

    ssl_analyzer_packet *a_p = visualizer_packet->mutable_analyzer_data();
    generateAnalyzerPacket(a_p);

    ssl_decision_packet *d_p = visualizer_packet->mutable_decision_data();
    generateDecisionPacket(d_p);

    ssl_planner_packet *p_p = visualizer_packet->mutable_planner_data();
    generatePlannerPacket(p_p);

    return visualizer_packet;
}

void GUIHandler::generateWorldPacket(ssl_world_packet *packet)
{
    if(packet == NULL)
        return;

    packet->mutable_comment()->append("This packet is filled in cyrus 2014 server.");
    {
    SSL::Side blueSide = (game->ourColor() == SSL::Blue)? game->ourSide():game->opponentSide();
    packet->mutable_blue_team()->set_side((blueSide==SSL::Left)?
                                    ssl_world_packet_Side_left:ssl_world_packet_Side_right);
    packet->mutable_yellow_team()->set_side((blueSide==SSL::Right)?
                                    ssl_world_packet_Side_left:ssl_world_packet_Side_right);
    }
    for(int tm=0; tm<2 ; ++tm)
    {
//        vector<SSLRobot* > team_robots = world->getTeam((Color)tm)->inFields();
        vector<SSLRobot* > team_robots = world->getTeam((Color)tm)->allRobots();
        for(uint i=0; i < team_robots.size() ; ++i)
        {
            const SSLRobot* robot = team_robots[i];
            ssl_world_packet_Robot* robot_packet = (((Color)tm==Blue)?
                    packet->mutable_blue_team()->add_robots() : packet->mutable_yellow_team()->add_robots());
            robot_packet->set_id(robot->id);
            robot_packet->mutable_position()->set_x(robot->Position().X());
            robot_packet->mutable_position()->set_y(robot->Position().Y());
            robot_packet->mutable_position()->set_teta(robot->Position().Teta());

            robot_packet->mutable_velecity()->set_x(robot->Speed().X());
            robot_packet->mutable_velecity()->set_y(robot->Speed().Y());
            robot_packet->mutable_velecity()->set_teta(robot->Speed().Teta());
        }
    }

    ssl_world_packet_Ball* ball_packet = packet->mutable_field_balls()->Add();
    ball_packet->mutable_position()->set_x(world->mainBall()->Position().X());
    ball_packet->mutable_position()->set_y(world->mainBall()->Position().Y());
    ball_packet->mutable_position()->set_teta(0);

    ball_packet->mutable_velecity()->set_x(world->mainBall()->Speed().X());
    ball_packet->mutable_velecity()->set_y(world->mainBall()->Speed().Y());
    ball_packet->mutable_velecity()->set_teta(0);

    ball_packet->set_id(0);

    string referee_state_str;
    switch(world->m_refereeState) {
    case SSLReferee::Unknown:
        referee_state_str = "unknown";
        break;
    case SSLReferee::Halt:
        referee_state_str = "halt";
        break;
    case SSLReferee::Stop:
        referee_state_str = "stop";
        break;
    case SSLReferee::ForceStart:
        referee_state_str = "force-start";
        break;
    default:
        referee_state_str = "restart";
        break;
    }

    packet->set_referee_state(referee_state_str);
}

void GUIHandler::generateAnalyzerPacket(ssl_analyzer_packet *packet)
{
    if(packet == NULL)
        return;

    // test
    packet->set_comment("Test Analyzer Packet ");
    SSLAnalyzer::RobotIntersectTime nearest = analyzer->nearestRobotIntersectBall(SSL::Blue);
    if(nearest.isValid())
        packet->set_nearest_blue_id(nearest.m_robot->id);
    else
        packet->set_nearest_blue_id(0);// default nearest robot
    nearest = analyzer->nearestRobotIntersectBall(SSL::Yellow);
    if(nearest.isValid())
        packet->set_nearest_yellow_id(nearest.m_robot->id);
    else
        packet->set_nearest_yellow_id(0);
    SSLTeam * possessorTeam = analyzer->ballPossessorTeam();
    if(possessorTeam == NULL)
        packet->set_possessor_team(ssl_analyzer_packet_Color_none);
    else if(possessorTeam->color == SSL::Blue)
        packet->set_possessor_team(ssl_analyzer_packet_Color_blue);
    else if(possessorTeam->color == SSL::Yellow)
        packet->set_possessor_team(ssl_analyzer_packet_Color_yellow);



    nearest = analyzer->nearestRobotIntersectBall();
    if(nearest.isValid())
        packet->set_nearest_can_kick(analyzer->canKick(nearest.m_robot));
    else
        packet->set_nearest_can_kick(false);
    packet->set_is_game_running(analyzer->isGameRunning());

    vector<SSLRobot*> all_inFields = world->all_inFields();
    for(uint i=0; i< all_inFields.size(); i++) {
        SSLRobot* robot = all_inFields.at(i);
        SSLAnalyzer::RobotIntersectTime intersect_ = analyzer->whenWhereCanRobotCatchTheBall(robot);
        ssl_analyzer_packet_RobotIntersectTime* intersect_mes=  packet->add_intersects();
        intersect_mes->set_color((robot->color==SSL::Blue)? ssl_analyzer_packet_Color_blue:ssl_analyzer_packet_Color_yellow);
        intersect_mes->set_id(robot->id);
        intersect_mes->set_intersect_x(intersect_.m_position.X());
        intersect_mes->set_intersect_y(intersect_.m_position.Y());
        intersect_mes->set_time(intersect_.m_time);
    }
}

void GUIHandler::generatePlannerPacket(ssl_planner_packet *packet)
{
    packet->set_comment("This is planning packet");
    planner_polygon* bound = packet->mutable_plannerbound();
    vector<SSLAgent*>::iterator it;
    for(it = decision->m_agents.begin(); it!=decision->m_agents.end(); ++it)
    {
        SSLAgent* agent = *it;
        if(agent->isNull())
            return;
        planner_plan* plan = packet->add_plans();
        plan->set_id(agent->getID());
        planner_vec3d* initial = plan->mutable_initstate();
        initial->set_x(agent->robot->Position().X());
        initial->set_y(agent->robot->Position().Y());
        initial->set_teta(agent->robot->Position().Teta());

        planner_vec3d* goal = plan->mutable_goalstate();
        goal->set_x(agent->tempTarget.X());
        goal->set_y(agent->tempTarget.Y());
        goal->set_teta(agent->tempTarget.Teta());
        planner_obstacles* obstacles = plan->mutable_obstacleset(); // not filled yet
        if(agent->planner.planningResult)
            for(uint i = 0; i< agent->planner.getTrajectory().lenght(); i++)
            {
                Vector3D pos = agent->planner.getTrajectory().getStation(i).getPosition();
                planner_vec3d* state = plan->add_pathstate();
                state->set_x(pos.X());
                state->set_y(pos.Y());
                state->set_teta(pos.Teta());
            }
        plan->mutable_desiredvel()->set_x(agent->desiredGlobalSpeed.X() * 2000);
        plan->mutable_desiredvel()->set_y(agent->desiredGlobalSpeed.Y() * 2000);
        plan->mutable_desiredvel()->set_teta(agent->desiredGlobalSpeed.Teta() * 2000);

        plan->mutable_appliedvel()->set_x(agent->appliedGlobalSpeed.X() * 2000);
        plan->mutable_appliedvel()->set_y(agent->appliedGlobalSpeed.Y() * 2000);
        plan->mutable_appliedvel()->set_teta(agent->appliedGlobalSpeed.Teta() * 2000);
    }
}

void GUIHandler::generateDecisionPacket(ssl_decision_packet *packet)
{
    packet->set_comment("This is decision packet");
    packet->set_our_color((game->ourColor() == SSL::Blue)?
                ssl_decision_packet_Color_blue:ssl_decision_packet_Color_yellow);
    packet->set_our_side((game->ourSide() == SSL::Left)?
                ssl_decision_packet_Side_left:ssl_decision_packet_Side_right);

    packet->set_strategy_name(game->currentStrategy->m_name);
    for(uint i=0; i<game->m_agents.size(); i++) {
        SSLAgent* agent = game->m_agents[i];
        if(agent->isNull())
            continue;
        ssl_decision_packet_Robot_Role* robot_role = packet->add_robot_roles();
        robot_role->set_robot_id(agent->getID());
        string role_name = typeid(*(agent->role)).name();
        robot_role->set_current_role(role_name);
        robot_role->set_current_skill(agent->skill_in_use);
    }
}

bool GUIHandler::sendPacket(const ssl_visualizer_packet &p)
{
    ParameterManager* pm = ParameterManager::getInstance();
    string buffer;    
    p.SerializeToString(&buffer);
    Net::Address multiaddr;
    multiaddr.setHost(pm->get<string>("network.VISUALIZER_IP").c_str(),pm->get<int>("network.VISUALIZER_PORT"));
    bool result;
    mtx_.lock();
    result = this->send(buffer.c_str(), buffer.length(), multiaddr);

    mtx_.unlock();
    if (result==false)
    {
        cerr << "Sending Visualizer data failed (maybe too large?). Size was: " << buffer.length() << endl;
    }
    else
    {
        cout << buffer.length() << " Bytes of ( Visualizer Packet ) has been sent." << endl;
    }
    return(result);
}
