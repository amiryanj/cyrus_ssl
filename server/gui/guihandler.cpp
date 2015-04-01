#include "guihandler.h"
//#include "boost/shared_ptr.hpp"
#include "paramater-manager/parametermanager.h"
#include "../definition/SSLRobot.h"
#include "../definition/SSLBall.h"
#include "../soccer/sslstrategy.h"
#include "../soccer/sslagent.h"
#include "../soccer/sslrole.h"
#include "../vision/VisionFilter.h"

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
    openSocket(pm->get<int>("network.VISUALIZER_PORT"),pm->get<string>("network.VISUALIZER_ADDRESS"));
    return true;
}

bool GUIHandler::openSocket(int port, string address)
{
    this->close();
    if(!this->open(port, true, true))
    {
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

void GUIHandler::testVisualizer()
{
    ssl_visualizer_packet* visualizer_packet = new ssl_visualizer_packet();
    ssl_world_packet *w_p = visualizer_packet->mutable_world_data();
    generateWorldPacket(w_p);

    w_p->mutable_blue_team()->mutable_robots(0)->mutable_position()->set_x(0);
    w_p->mutable_blue_team()->mutable_robots(0)->mutable_position()->set_y(0);

    ssl_world_packet_Ball* ball_packet = w_p->mutable_field_balls()->Add();
    ball_packet->mutable_position()->set_x(200.0);
    ball_packet->mutable_position()->set_y(5.0);
    ball_packet->mutable_position()->set_teta(0);

    ball_packet->mutable_velocity()->set_x(7.0);
    ball_packet->mutable_velocity()->set_y(1.0);
    ball_packet->mutable_velocity()->set_teta(0);

    ball_packet->set_id(0);

    sendPacket(*visualizer_packet);
    if(visualizer_packet != NULL)
        delete visualizer_packet;

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
        vector<SSLRobot* > team_robots = world->getTeam((Color)tm)->getAllRobots();
        for(uint i=0; i < team_robots.size() ; ++i)
        {
            const SSLRobot* robot = team_robots[i];
            ssl_world_packet_Robot* robot_packet = (((Color)tm==Blue)?
                    packet->mutable_blue_team()->add_robots() : packet->mutable_yellow_team()->add_robots());
            robot_packet->set_id(robot->id);
            robot_packet->mutable_position()->set_x(robot->Position().X());
            robot_packet->mutable_position()->set_y(robot->Position().Y());
            robot_packet->mutable_position()->set_teta(robot->Position().Teta());

            robot_packet->mutable_velocity()->set_x(robot->Speed().X());
            robot_packet->mutable_velocity()->set_y(robot->Speed().Y());
            robot_packet->mutable_velocity()->set_teta(robot->Speed().Teta());
        }
    }

    ssl_world_packet_Ball* ball_packet = packet->mutable_field_balls()->Add();
    ball_packet->mutable_position()->set_x(world->mainBall()->Position().X());
    ball_packet->mutable_position()->set_y(world->mainBall()->Position().Y());
    ball_packet->mutable_position()->set_teta(0);

    ball_packet->mutable_velocity()->set_x(world->mainBall()->Speed().X());
    ball_packet->mutable_velocity()->set_y(world->mainBall()->Speed().Y());
    ball_packet->mutable_velocity()->set_teta(0);

    Vector2D ball_displacement = VisionFilter::getInstance()->ballFilter->m_displacement;
    ball_packet->mutable_displacement()->set_x(ball_displacement.X());
    ball_packet->mutable_displacement()->set_y(ball_displacement.Y());
    ball_packet->mutable_displacement()->set_teta(0);

    Vector2D ball_raw_velocity = VisionFilter::getInstance()->ballFilter->m_rawVelocity;
    ball_packet->mutable_velocity_raw()->set_x(ball_raw_velocity.X());
    ball_packet->mutable_velocity_raw()->set_y(ball_raw_velocity.Y());
    ball_packet->mutable_velocity_raw()->set_teta(0);

    Vector2D ball_acceleration = VisionFilter::getInstance()->ballFilter->m_acceleration;
    ball_packet->mutable_acceleration()->set_x(ball_acceleration.X());
    ball_packet->mutable_acceleration()->set_y(ball_acceleration.Y());
    ball_packet->mutable_acceleration()->set_teta(0);


    ball_packet->set_id(0);

#define Str(x)  #x

    string referee_state_str;
    switch(world->m_refereeState) {
    case SSLReferee::Unknown:
        referee_state_str = "Unknown";
        break;
    case SSLReferee::Halt:
        referee_state_str = "Halt";
        break;
    case SSLReferee::Stop:
        referee_state_str = "Stop";
        break;
    case SSLReferee::ForceStart:
        referee_state_str = "Force Start";
        break;
    case SSLReferee::BlueKickOffPosition:
        referee_state_str = "Blue KickOff Position";
        break;
    case SSLReferee::YellowKickOffPosition:
        referee_state_str = "Yellow KickOff Position";
        break;
    case SSLReferee::BlueKickOffKick:
        referee_state_str = "Blue KickOff Kick";
        break;
    case SSLReferee::YellowKickOffKick:
        referee_state_str = "Yellow KickOff Kick";
        break;
    case SSLReferee::BluePenaltyPosition:
        referee_state_str = "Blue Penalty Position";
        break;
    case SSLReferee::YellowPenaltyPosition:
        referee_state_str = "Yellow Penalty Position";
        break;
    case SSLReferee::BluePenaltyKick:
        referee_state_str = "Blue Penalty Kick";
        break;
    case SSLReferee::YellowPenaltyKick:
        referee_state_str = "Yellow Penalty Kick";
        break;
    case SSLReferee::BlueDirectKick:
        referee_state_str = "Blue Direct Kick";
        break;
    case SSLReferee::YellowDirectKick:
        referee_state_str = "Yellow Direct Kick";
        break;
    case SSLReferee::BlueIndirectKick:
        referee_state_str = "Blue Indirect Kick";
        break;
    case SSLReferee::YellowIndirectKick:
        referee_state_str = "Yellow Indirect Kick";
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

    vector<SSLRobot*> all_inFields = world->getInFieldRobots();
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
        goal->set_x(agent->skill->target.X());
        goal->set_y(agent->skill->target.Y());
        goal->set_teta(agent->skill->target.Teta());
        planner_obstacles* obstacles = plan->mutable_obstacleset(); // not filled yet
        if(agent->skill->planner.planningResult)
            for(uint i = 0; i< agent->skill->planner.getTrajectory().length(); i++)
            {
                Vector3D pos = agent->skill->planner.getTrajectory().getStation(i).getPosition();
                planner_vec3d* state = plan->add_pathstate();
                state->set_x(pos.X());
                state->set_y(pos.Y());
                state->set_teta(pos.Teta());
            }
        plan->mutable_desiredvel()->set_x(agent->skill->desiredGlobalSpeed.X());
        plan->mutable_desiredvel()->set_y(agent->skill->desiredGlobalSpeed.Y());
        plan->mutable_desiredvel()->set_teta(agent->skill->desiredGlobalSpeed.Teta());

        plan->mutable_appliedvel()->set_x(agent->skill->appliedGlobalSpeed.X());
        plan->mutable_appliedvel()->set_y(agent->skill->appliedGlobalSpeed.Y());
        plan->mutable_appliedvel()->set_teta(agent->skill->appliedGlobalSpeed.Teta());
    }
}

void GUIHandler::generateDecisionPacket(ssl_decision_packet *packet)
{
    packet->set_comment("This is decision packet");
    packet->set_our_color((game->ourColor() == SSL::Blue)?
                ssl_decision_packet_Color_blue:ssl_decision_packet_Color_yellow);
    packet->set_our_side((game->ourSide() == SSL::Left)?
                ssl_decision_packet_Side_left:ssl_decision_packet_Side_right);

    if(game->currentStrategy != NULL)
        packet->set_strategy_name(game->currentStrategy->m_name);
    for(uint i=0; i<game->m_agents.size(); i++) {
        SSLAgent* agent = game->m_agents[i];
        if(agent->isNull())
            continue;
        ssl_decision_packet_Robot_Role* robot_role = packet->add_robot_roles();
        robot_role->set_robot_id(agent->getID());
        string role_name = typeid(*(agent->role)).name();
        robot_role->set_current_role(role_name);
        robot_role->set_current_skill(agent->skill->name);
    }
}

bool GUIHandler::sendPacket(const ssl_visualizer_packet &p)
{
    ParameterManager* pm = ParameterManager::getInstance();
    string buffer;    
    p.SerializeToString(&buffer);
    Net::Address multiaddr;
    multiaddr.setHost(pm->get<string>("network.VISUALIZER_ADDRESS").c_str(),
                      pm->get<int>("network.VISUALIZER_PORT"));
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
