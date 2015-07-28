#include "grsimsender.h"
#include <QDebug>
#include <paramater-manager/parametermanager.h>
GRSimSender::GRSimSender(Color our_color)
{
    ourColor = our_color;
}

bool GRSimSender::openSocket()
{
    ParameterManager* pm = ParameterManager::getInstance();
    return openSocket(pm->get<int>("network.GRSIM_COMMAND_PORT"));
}

bool GRSimSender::openSocket(int port)
{
    ParameterManager* pm = ParameterManager::getInstance();

    connected = false;
    this->close();
//  //  this->open(port, true, true)
//    if(!this->bind(port, QUdpSocket::ShareAddress))
//    {
//        cerr << "GRSIM Unable to open UDP network port: "<< port << endl;
//      //  return false;
//    }

//    //Net::Address multiaddr, interface;
//   // multiaddr.setHost(p.c_str(), port);
//  //  interface.setAny();
//    QHostAddress addr(QString(pm->get<string>("network.GRSIM_COMMAND_ADDRESS").c_str()));
//    if(!this->joinMulticastGroup(addr))
//    {
//        cerr << "Unable to setup UDP multicast, for grsim connection" << endl ;
//    }
    cout << "Grsim Sender UDP network successfully configured. Multicast address= " << port << endl;
    connected = true;
    return true;
}

void GRSimSender::sendPacket(int robotID, RobotCommandPacket rawPacket)
{
    ParameterManager* pm = ParameterManager::getInstance();
    grSim_Packet grSimPacket;
    grSimPacket.mutable_commands()->set_isteamyellow((ourColor==Yellow));
    grSimPacket.mutable_commands()->set_timestamp(0.0);

    grSim_Robot_Command* command = grSimPacket.mutable_commands()->add_robot_commands();
    command->set_id(robotID);
    double max_lin_vel = 0.01; // you should set this parameter
    command->set_wheel1(rawPacket.getWheelSpeed(4)/max_lin_vel);
    command->set_wheel2(rawPacket.getWheelSpeed(3)/max_lin_vel);
    command->set_wheel3(rawPacket.getWheelSpeed(2)/max_lin_vel);
    command->set_wheel4(rawPacket.getWheelSpeed(1)/max_lin_vel);
    command->set_wheelsspeed(true);
    if(rawPacket.byWheelSpeed){
        command->set_wheelsspeed(true);

    }
    else
    {        
        double d_sign = (rawPacket.getVelocity().Y() >= 0)? 1:-1;
        command->set_velnormal(rawPacket.getVelocity().lenght2D() * -d_sign / max_lin_vel);
        command->set_veltangent(tan(M_PI_2 + atan2(rawPacket.getVelocity().Y(), rawPacket.getVelocity().X())));
        command->set_velangular(rawPacket.getVelocity().Teta());


       // command->set_velnormal(rawPacket.getVelocity().X());
       // command->set_veltangent(rawPacket.getVelocity().Y());
       // command->set_velangular(0);
       // qDebug() << rawPacket.getVelocity().X() << " " << rawPacket.getVelocity().Y() << " " << rawPacket.getVelocity().Teta();
    }
    // dangerous test
   /* command->set_velnormal(-2);
    command->set_veltangent(0);
    command->set_velangular(0);*/

    command->set_kickspeedx(rawPacket.m_kickPower);
    command->set_kickspeedz(0); // chip kick
    command->set_spinner((rawPacket.m_isDribbler)? 1:0);

    if(connected)
    {
        std::string s;
        grSimPacket.SerializeToString(&s);
       // Net::Address multiaddr;
      //  multiaddr.setHost(pm->get<string>("network.GRSIM_COMMAND_ADDRESS").c_str(),
                    //      pm->get<int>("network.GRSIM_COMMAND_PORT"));
       QHostAddress adr(pm->get<string>("network.GRSIM_COMMAND_ADDRESS").c_str());
        quint16 port =pm->get<int>("network.GRSIM_COMMAND_PORT");
       this->writeDatagram(s.c_str(),s.length(),adr,port);
        //this->send(s.c_str(), s.length(), multiaddr);
    }
}

