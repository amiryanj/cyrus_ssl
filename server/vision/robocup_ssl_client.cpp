//========================================================================
//  This software is free: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License Version 3,
//  as published by the Free Software Foundation.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  Version 3 in the file COPYING that came with this distribution.
//  If not, see <http://www.gnu.org/licenses/>.
//========================================================================
/*!
  \file    robocup_ssl_client.cpp
  \brief   C++ Implementation: robocup_ssl_client
  \author  Stefan Zickler, 2009
*/
//========================================================================
#include "robocup_ssl_client.h"
#include <QtGlobal>
#include <QNetworkInterface>
#include <iostream>

using namespace std;
RoboCupSSLClient::RoboCupSSLClient(int port,
                     string net_address,
                     string net_interface)
{
  _port=port;
  _net_address=net_address;
  _net_interface=net_interface;
  in_buffer=new char[65536];
}


RoboCupSSLClient::~RoboCupSSLClient()
{
  delete[] in_buffer;
}

void RoboCupSSLClient::close() {
  socket.close();
}

bool RoboCupSSLClient::open(bool blocking) {
  close();
  //mc.open(_port,true,true,blocking);

#if QT_VERSION >= 0x050000
    if(socket.bind(QHostAddress::AnyIPv4, _port,  QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint));
#else
    if(socket.bind(QHostAddress::Any, _port, QUdpSocket::ShareAddress));
#endif
  {
    fprintf(stderr,"Unable to open UDP network port: %d\n",_port);
    fflush(stderr);
//    return(false);
  }

  //Net::Address multiaddr, interface;
  //QNetworkInterface multiaddr;
    QHostAddress m_groupAddress(QString(_net_address.c_str()));
    foreach (const QNetworkInterface& iface, QNetworkInterface::allInterfaces()) {
        socket.joinMulticastGroup(m_groupAddress, iface);
    }

  //if(!socket.joinMulticastGroup(QHostAddress())
 // {
   //   fprintf(stderr,"NEW Unable to setup UDP multicast\n");
  //}
 // else {
      fprintf(stderr,"SSLVision joined ... \n");
//  }
 // multiaddr.setHost(_net_address.c_str(),_port);
 /* if(_net_interface.length() > 0){
    interface.setHost(_net_interface.c_str(),_port);
  }else{
    interface.setAny();
  }

  if(!mc.addMulticast(multiaddr,interface)) {
    fprintf(stderr,"Unable to setup UDP multicast\n");
    fflush(stderr);
    return(false);
  }
*/
  return(true);
}

bool RoboCupSSLClient::receive(SSL_WrapperPacket & packet, int msec) {
    int r = 0;
    //  if (socket.hasPendingDatagrams()) {
    if(socket.waitForReadyRead(msec)) {
        r=socket.readDatagram(in_buffer, MaxDataGramSize);
      //  cout << "Vision packet received: Size <<" << r << endl;
        return packet.ParseFromArray(in_buffer, r);
    }
    return false;
}
