#include "guihandler.h"

GUIHandler::GUIHandler()
{

}

void GUIHandler::check()
{

}

void GUIHandler::generateWorldPacket()
{
    world_packet.Clear();

    world_packet.mutable_blue_team()->set_color(blue_color);
    world_packet.mutable_yellow_team()->set_color(yellow_color);

    world_packet.mutable_blue_team()->set_side((world()->team[Blue]->side==Left)? left_side:right_side);
    world_packet.mutable_yellow_team()->set_side((world()->team[Yellow]->side==Left)? left_side:right_side);

    for(int tm=0; tm<2 ; ++tm)
    {
        for(uint i=0; i<world()->getTeam((Color)tm)->numInFieldRobots(); ++i)
        {
            const SSLRobot* robot = world()->getTeam((Color)tm)->inFieldRobots()[i];
            ssl_robot* robot_packet = (((Color)tm==Blue)?
                    world_packet.mutable_blue_team()->add_robots() : world_packet.mutable_yellow_team()->add_robots());
            robot_packet->mutable_position()->set_x(robot->Position().X());
            robot_packet->mutable_position()->set_y(robot->Position().Y());
            robot_packet->mutable_position()->set_teta(robot->Position().Teta());

            robot_packet->mutable_velecity()->set_x(robot->Speed().X());
            robot_packet->mutable_velecity()->set_y(robot->Speed().Y());
            robot_packet->mutable_velecity()->set_teta(robot->Speed().Teta());
        }
    }
//    world_packet.mutable_field_balls()->Add();
    ssl_ball* ball_packet = world_packet.mutable_field_balls()->Add();
    ball_packet->mutable_position()->set_x(world()->ball->Position().X());
    ball_packet->mutable_position()->set_y(world()->ball->Position().Y());
    ball_packet->mutable_position()->set_teta(0);

    ball_packet->mutable_velecity()->set_x(world()->ball->Speed().X());
    ball_packet->mutable_velecity()->set_y(world()->ball->Speed().Y());
    ball_packet->mutable_velecity()->set_teta(0);

}

void GUIHandler::generateAnalyzerPacket()
{

}

void GUIHandler::generateGamePacket()
{

}

bool GUIHandler::sendPacket(ssl_visualizer_packet *packet)
{
    string buffer;
    packet->SerializeToString(&buffer);
    Net::Address multiaddr;
    multiaddr.setHost(VISUALIZER_IP, VISUALIZER_PORT);
    bool result;
    mtx_.lock();
    result = this->send(buffer.c_str(), buffer.length(), multiaddr);
    mtx_.unlock();
    if (result==false) {
        cerr << "Sending UDP datagram failed (maybe too large?). Size was: " << buffer.length() << endl;
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
