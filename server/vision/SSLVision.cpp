#include "SSLVision.h"
#include "Frame.h"
#include "VisionFilter.h"
#include <exception>

IPPacket SSLVision::m_temp_packet;
QUdpSocket SSLVision::socket_;
//UDP SSLVision::udp_socket;
//boost::asio::ip::udp::socket * SSLVision::boost_socket = NULL;

SSLVision::SSLVision(int port, const string address) // :UDP() // , SSLListener()
{
    socket_.bind(port);
//    m_socket = new QUdpSocket();
//    m_socket->bind(port, QUdpSocket::ShareAddress);
//    m_socket->joinMulticastGroup(QHostAddress(QString(address.c_str())));
//    QObject::connect(m_socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
//    QObject::connect(this, SIGNAL(testSignal()), this, SLOT(readSocket()));

//    udp_socket.open(port, true, true, false);
//    Address multi_, interface_;
//    interface_.setAny();
//    multi_.setHost(address.c_str(), port);
//    if(!udp_socket.addMulticast(multi_, interface_)) {
//        cerr << "Unable to setup UDP multicast, for vision connection" << endl ;
//    } else {
//        cout << "Vision UDP network successfully configured. Multicast address= " << port << endl;
//    }

/// ###################### using boost library ############################
//    try {
//        boost::asio::io_service io_serv;
//        boost_socket = new udp::socket(io_serv);
//        boost_socket->open(boost::asio::ip::udp::v4());
//        bool is_boost_socket_open = boost_socket->is_open();

//        cout << "Is boost_socket (vision) open ? " << is_boost_socket_open << endl;
//        boost_socket->set_option(boost::asio::ip::udp::socket::reuse_address(true));
////        boost_socket->bind(boost::asio::ip::udp::endpoint(udp::v4(), port));

//    }
//    catch (std::exception& excep) {
//        cerr << "vision socket problem: " << excep.what() << endl;
//    }


    pthread_create(&ssl_vision_thread, NULL, &check, NULL);

}

SSLVision::~SSLVision() { }

void *SSLVision::check(void *)
{
    while(true)
    {
//        std::size_t bytes_ = boost_socket->available();
//        boost::array<char, 1024> recv_buffer_;
//        boost_socket->receive(boost::asio::buffer(m_temp_packet.buffer, 4096));
        while( socket_.hasPendingDatagrams() ) {
            m_temp_packet.length = socket_.pendingDatagramSize();
            socket_.readDatagram(m_temp_packet.buffer, m_temp_packet.length);
            cout << "Vision-Packet received. Packet Lenght: [" << m_temp_packet.length << "]" << endl;
//            m_temp_packet.buffer = recv_buffer_.c_array();
//            m_temp_packet.length = recv_buffer_.size();

            SSL_WrapperPacket wrapper;
            wrapper.Clear();

            wrapper.ParseFromArray(m_temp_packet.buffer, m_temp_packet.length);

            updateFilterModule(wrapper);
        }

//        if(udp_socket.havePendingData()) {
//        Address sender_adress;
//            m_temp_packet.length = udp_socket.recv(m_temp_packet.buffer, MAX_BUFFER_SIZE, sender_adress);
//            cout << "Vision-Packet received. Packet Lenght: [" << m_temp_packet.length << "]" << endl;

//            SSL_WrapperPacket wrapper;
//            wrapper.Clear();
//            wrapper.ParseFromArray(m_temp_packet.buffer, m_temp_packet.length);

//            updateFilterModule(wrapper);
//        }

        VisionFilter::getInstance()->check();
        usleep(4000);
    }
}

void SSLVision::updateFilterModule(const SSL_WrapperPacket &wrapper)
{
	//TODO: update world model from wrapper    
    if(wrapper.has_detection())
    {        
        Frame temp_frame;
        for(int i=0; i < wrapper.detection().robots_blue_size(); i++)
        {
            SSL_DetectionRobot Robot = wrapper.detection().robots_blue(i);
            temp_frame.setToCurrentTimeMilliSec();
            temp_frame.position = Vector3D(Robot.x(), Robot.y(), Robot.orientation());
            temp_frame.confidence = Robot.confidence();
            temp_frame.camera_id = wrapper.detection().camera_id();
            VisionFilter::getInstance()->setRobotFrame(SSL::Blue, Robot.robot_id(), temp_frame);
        }

        for(int i=0; i< wrapper.detection().robots_yellow_size(); i++)
        {
            SSL_DetectionRobot Robot = wrapper.detection().robots_yellow(i);
            temp_frame.setToCurrentTimeMilliSec();
            temp_frame.position = Vector3D(Robot.x(), Robot.y(), Robot.orientation());
            temp_frame.confidence = Robot.confidence();
            temp_frame.camera_id = wrapper.detection().camera_id();
            VisionFilter::getInstance()->setRobotFrame(SSL::Yellow, Robot.robot_id(), temp_frame);
        }

        vector<Frame> balls_vec;
        for(int i=0; i< wrapper.detection().balls_size(); i++)
        {
            SSL_DetectionBall Ball = wrapper.detection().balls(i);
            temp_frame.setToCurrentTimeMilliSec();
            temp_frame.position = Vector2D(Ball.x(), Ball.y()).to3D();            
            temp_frame.confidence = Ball.confidence();
            temp_frame.camera_id = wrapper.detection().camera_id();
            balls_vec.push_back(temp_frame);
        }
        VisionFilter::getInstance()->setBallFrames(balls_vec);
    }
    if(wrapper.has_geometry())
    {
        SSL_GeometryData geometryData = wrapper.geometry();
        // and so on
    }
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
