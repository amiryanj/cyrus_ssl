#include "sslvision.h"
#include "visionfilter.h"
#include "../paramater-manager/parametermanager.h"

#if QT_VERSION >= 0x050000
#include <QtConcurrent>
#else
#include <QtCore>
#endif

RoboCupSSLClient* SSLVision::client;
bool SSLVision::idle = false;

SSLVision::SSLVision(int port, const string address) // :UDP() // , SSLListener()
{
    client = new RoboCupSSLClient(port, address, "");
    client->open(true);
    QtConcurrent::run(check, (void *)NULL);
}

SSLVision::~SSLVision()
{
}

void SSLVision::setIdle(bool i)
{
    idle = i;
}

void* SSLVision::check(void *)
{
    static long packet_counter = 0;
    SSL_WrapperPacket wrapper;
    while(true) {
        if(idle) {
            sleep(1); // 1 second
            continue;
        }
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
    return 0;
}

