#include "sslvision.h"
#include "visionfilter.h"
#include "../paramater-manager/parametermanager.h"

#if QT_VERSION >= 0x050000
#include <QtConcurrent>
#else
#include <QtCore>
#endif

Net::UDP SSLVision::simple_socket;
RoboCupSSLClient* SSLVision::client;

SSLVision::SSLVision(int port, const string address) // :UDP() // , SSLListener()
{
//    m_socket = new QUdpSocket();
//    m_socket->bind(port, QUdpSocket::ShareAddress);
//    m_socket->joinMulticastGroup(QHostAddress(QString(address.c_str())));
//    QObject::connect(m_socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
//    QObject::connect(this, SIGNAL(testSignal()), this, SLOT(readSocket()));

    client = new RoboCupSSLClient(port, address, "");
    client->open(true);

//    simple_socket.open(port, true, true);
//    Address multi_, interface_;
//    multi_.setHost(address.c_str(), port);
//    interface_.setAny();
//    simple_socket.addMulticast(multi_, interface_);

   // pthread_create(&ssl_vision_thread, NULL, &check, NULL);
    QtConcurrent::run(check, (void *)NULL);
}

SSLVision::~SSLVision()
{
}

void* SSLVision::check(void *)
{
    static long packet_counter = 0;
    SSL_WrapperPacket wrapper;
    while(true) {
        if(client->receive(wrapper)) {
            if(wrapper.has_detection()){
                packet_counter ++;
                if(packet_counter % 60 == 0)
                    cout << "Vision Packet # [" << packet_counter << "]" << endl;
//                cout << "\tCamera ID: " << wrapper.detection().camera_id();
//                cout << "\tFrame Number: " << wrapper.detection().frame_number() << endl;
//                cout << "\t Frame capture time:" << (long)(wrapper.detection().t_capture() *1000000.0) << " (us)" << endl;
                VisionFilter::getInstance()->update(wrapper);
                VisionFilter::getInstance()->check();
            }
        }
        QThread::currentThread()->msleep(1);
    }
//    Address sender_adress;
//    while(true)
//    {
//        if(simple_socket.havePendingData())
//        {
//            m_temp_packet.length = simple_socket.recv(m_temp_packet.buffer, MAX_BUFFER_SIZE, sender_adress);
//            if(m_temp_packet.length == 0)
//                continue;
//            packet_counter ++;
//            cout << packet_counter << "] Vision-Packet received. Packet Lenght: [" << m_temp_packet.length << "]" << endl;

//            SSL_WrapperPacket wrapper;
//            wrapper.Clear();
//            wrapper.ParseFromArray(m_temp_packet.buffer, m_temp_packet.length);

//            updateFilterModule(wrapper);
//        }
//        VisionFilter::getInstance()->check();
//        usleep(1000);
//    }
    return 0;
}


//void SSLVision::readSocket()
//{
//    while(m_socket->hasPendingDatagrams()) {

//        QByteArray data;

//        data.resize(m_socket->pendingDatagramSize());
//        m_socket->readDatagram(data.data(), data.size());

//        cout << "Vision-Packet received. Packet Lenght: [" << data.size() << "]" << endl;

//        SSL_WrapperPacket wrapper;
//        wrapper.Clear();
//        wrapper.ParseFromArray(data.data(), data.size());//m_temp_packet.buffer, m_temp_packet.length);

//        updateFilterModule(wrapper);
//    }
//}
