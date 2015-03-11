#ifndef _SSLVISION_H_
#define _SSLVISION_H_

#include "../../common/thirdparty/socket/IPPacket.h"
#include "../../common/protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <QtNetwork/QUdpSocket>

//#include <QtNetwork/QUdpSocket>

#include "../../common/thirdparty/socket/netraw.h"
using namespace Net;
using namespace boost::asio::ip;

#include <pthread.h>

class SSLVision //: public UDP //, public SSLListener
{
//    static UDP udp_socket;
    static QUdpSocket qudp_socket;
    static IPPacket m_temp_packet;

    static UDP simple_socket;

//    static boost::asio::ip::udp::socket *boost_socket;


    pthread_t ssl_vision_thread;

    static void *check(void *);
    static void updateFilterModule(const SSL_WrapperPacket& wrapper);

public:
    SSLVision(int port = 0, const std::string address = "");
	virtual ~SSLVision();


};

#endif /* _SSLVISION_H_ */
