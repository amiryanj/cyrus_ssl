#include "grsimsender.h"

GRSimSender::GRSimSender(Color our_color)
{
    ourColor = our_color;
}

bool GRSimSender::openSocket(int port)
{
    connected = false;
    this->close();
    if(!this->open(port, true, true))
    {
        cerr << "Unable to open UDP network port: "<< port << endl;
        return false;
    }

    Net::Address multiaddr, interface;
    multiaddr.setHost(GRSIM_VISION_ADDRESS, port);
    interface.setAny();

    if(!this->addMulticast(multiaddr, interface))
    {
        cerr << "Unable to setup UDP multicast." << endl ;
    }
    cout << "Visualizer UDP network successfully configured. Multicast address= " << port << endl;
    connected = true;
    return true;
}

void GRSimSender::sendPacket(int robotID, RobotCommandPacket rawPacket)
{
    grSim_Packet grSimPacket;
    grSimPacket.mutable_commands()->set_isteamyellow((ourColor==Yellow));
    grSimPacket.mutable_commands()->set_timestamp(0.0);

    grSim_Robot_Command* command = grSimPacket.mutable_commands()->add_robot_commands();
    command->set_id(robotID);

    command->set_wheelsspeed(true);
    command->set_wheel1(rawPacket.v[0]);
    command->set_wheel2(rawPacket.v[1]);
    command->set_wheel3(rawPacket.v[2]);
    command->set_wheel4(rawPacket.v[3]);

//    command->set_velnormal(rawPacket.vel_normal);
//    command->set_veltangent(tan(rawPacket.vel_radian));
//    command->set_velangular(rawPacket.vel_angular);

    command->set_kickspeedx(rawPacket.kickPower);
    command->set_kickspeedz(0); // chip kick
    command->set_spinner((rawPacket.isDribbler)? 1:0);

    if(connected)
    {
        std::string s;
        grSimPacket.SerializeToString(&s);
        Net::Address multiaddr;
        multiaddr.setHost(GRSIM_VISION_ADDRESS, GRSIM_COMMAND_PORT);
        this->send(s.c_str(), s.length(), multiaddr);
    }
}

void GRSimSender::check()
{

}