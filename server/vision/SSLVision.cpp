#include "SSLVision.h"
#include "Frame.h"
#include "VisionFilter.h"
#include "paramater-manager/parametermanager.h"

IPPacket SSLVision::m_temp_packet;
ofstream SSLVision::file;
UDP SSLVision::simple_socket;

SSLVision::SSLVision(int port, const string address) // :UDP() // , SSLListener()
{
//    m_socket = new QUdpSocket();
//    m_socket->bind(port, QUdpSocket::ShareAddress);
//    m_socket->joinMulticastGroup(QHostAddress(QString(address.c_str())));
//    QObject::connect(m_socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
//    QObject::connect(this, SIGNAL(testSignal()), this, SLOT(readSocket()));

    ParameterManager* pm = ParameterManager::getInstance();
    file.open(pm->get<string>("debug.ball").c_str());
    simple_socket.open(port, true, true);
    Address multi_, interface_;
    multi_.setHost(address.c_str(), port);
    interface_.setAny();
    simple_socket.addMulticast(multi_, interface_);

    pthread_create(&ssl_vision_thread, NULL, &check, NULL);


}

SSLVision::~SSLVision() { file.close();}

void* SSLVision::check(void *)
{
    Address sender_adress;
    while(true)
    {
        if(simple_socket.havePendingData())
        {
            m_temp_packet.length = simple_socket.recv(m_temp_packet.buffer, MAX_BUFFER_SIZE, sender_adress);
            cout << "Vision-Packet received. Packet Lenght: [" << m_temp_packet.length << "]" << endl;

            SSL_WrapperPacket wrapper;
            wrapper.Clear();
            wrapper.ParseFromArray(m_temp_packet.buffer, m_temp_packet.length);

            updateFilterModule(wrapper);            
        }
        VisionFilter::getInstance()->check();
        usleep(1000);
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

            file <<i << " , " << temp_frame.timeStampMilliSec<< ", ";
            file << Ball.x() <<" , " << Ball.y() << endl;
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
