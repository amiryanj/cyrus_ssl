#include "guihandler.h"
//#include "boost/shared_ptr.hpp"

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

bool GUIHandler::openSocket(int port)
{
    this->close();
    if(!this->open(port, true, true))
    {
        cerr << "Unable to open UDP network port: "<< port << endl;
        return false;
    }

    Net::Address multiaddr, interface;
    multiaddr.setHost(VISUALIZER_IP, port);
    interface.setAny();

    if(!this->addMulticast(multiaddr, interface))
    {
        cerr << "Unable to setup UDP multicast." << endl ;
    }
    cout << "Visualizer UDP network successfully configured. Multicast address= " << port << endl;
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
    packet->mutable_blue_team()->set_color(blue_color);
    packet->mutable_yellow_team()->set_color(yellow_color);

    packet->mutable_blue_team()->set_side((world()->team[Blue]->side==Left)? left_side:right_side);
    packet->mutable_yellow_team()->set_side((world()->team[Yellow]->side==Left)? left_side:right_side);

    for(int tm=0; tm<2 ; ++tm)
    {
        for(uint i=0; i<world()->getTeam((Color)tm)->numInFieldRobots(); ++i)
        {
            const SSLRobot* robot = world()->getTeam((Color)tm)->inFieldRobots()[i];
            ssl_robot* robot_packet = (((Color)tm==Blue)?
                    packet->mutable_blue_team()->add_robots() : packet->mutable_yellow_team()->add_robots());
            robot_packet->mutable_position()->set_x(robot->Position().X());
            robot_packet->mutable_position()->set_y(robot->Position().Y());
            robot_packet->mutable_position()->set_teta(robot->Position().Teta());

            robot_packet->mutable_velecity()->set_x(robot->Speed().X());
            robot_packet->mutable_velecity()->set_y(robot->Speed().Y());
            robot_packet->mutable_velecity()->set_teta(robot->Speed().Teta());
        }
    }
    ssl_ball* ball_packet = packet->mutable_field_balls()->Add();
    ball_packet->mutable_position()->set_x(world()->ball->Position().X());
    ball_packet->mutable_position()->set_y(world()->ball->Position().Y());
    ball_packet->mutable_position()->set_teta(0);

    ball_packet->mutable_velecity()->set_x(world()->ball->Speed().X());
    ball_packet->mutable_velecity()->set_y(world()->ball->Speed().Y());
    ball_packet->mutable_velecity()->set_teta(0);
}

void GUIHandler::generateAnalyzerPacket(ssl_analyzer_packet *packet)
{
}

void GUIHandler::generatePlannerPacket(ssl_planner_packet *packet)
{
}

void GUIHandler::generateDecisionPacket(ssl_decision_packet *packet)
{
}

bool GUIHandler::sendPacket(const ssl_visualizer_packet &p)
{
    string buffer;
    p.SerializeToString(&buffer);
    Net::Address multiaddr;
    multiaddr.setHost(VISUALIZER_IP, VISUALIZER_PORT);
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

SSLWorldModel *GUIHandler::world()
{
    return SSLWorldModel::getInstance();
}

SSLAnalyzer *GUIHandler::analyzer()
{
    return SSLAnalyzer::getInstance();
}

SSLGame *GUIHandler::game()
{
    return SSLGame::getInstance();
}