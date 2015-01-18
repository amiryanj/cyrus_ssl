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
    multiaddr.setHost(GRSIM_COMMAND_ADDRESS, port);
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
    double max_lin_vel = 10; // you should set this parameter
    if(rawPacket.byWheelSpeed){
        command->set_wheelsspeed(true);
        command->set_wheel1(rawPacket.getWheelSpeed(4)/max_lin_vel);
        command->set_wheel2(rawPacket.getWheelSpeed(3)/max_lin_vel);
        command->set_wheel3(rawPacket.getWheelSpeed(2)/max_lin_vel);
        command->set_wheel4(rawPacket.getWheelSpeed(1)/max_lin_vel);
    }
    else
    {        
        double d_sign = (rawPacket.getVelocity().Y() >= 0)? 1:-1;
        command->set_velnormal(rawPacket.getVelocity().lenght2D() * -d_sign / max_lin_vel);
        command->set_veltangent(tan(M_PI_2 + atan2(rawPacket.getVelocity().Y(), rawPacket.getVelocity().X())));
        command->set_velangular(rawPacket.getVelocity().Teta());
    }
    // dangerous test
//    command->set_velnormal(-2);
//    command->set_veltangent(tan(0));

    command->set_kickspeedx(rawPacket.m_kickPower);
    command->set_kickspeedz(0); // chip kick
    command->set_spinner((rawPacket.m_isDribbler)? 1:0);

    if(connected)
    {
        std::string s;
        grSimPacket.SerializeToString(&s);
        Net::Address multiaddr;
        multiaddr.setHost(GRSIM_COMMAND_ADDRESS, GRSIM_COMMAND_PORT);
        this->send(s.c_str(), s.length(), multiaddr);
    }
}

