#include "ai/SSLGame.h"
#include "ai/SSLAnalyzer.h"

#include <time.h>
#include "mainwindow.h"
#include "vision/sslvision.h"
#include "vision/robotclusterfilter.h"
#include "vision/visionfilter.h"
#include "referee/SSLReferee.h"
#include "gui/guihandler.h"
#include "transmitter/commandtransmitter.h"
#include "paramater-manager/parametermanager.h"
#include "test/testvisioninput.h"
#include "test/testskills.h"
#include "test/testreferee.h"
#include "test/testmathfunctions.h"
#include "debug-tools/logger.h"
#include "debug-tools/networkplotter.h"
#include "debug-tools/debugclient.h"
#include "debug-tools/builtindebug.h"
#include "general.h"
#include "transmitter/RobotCommandPacket.h"
#include <QApplication>
using namespace std;

MainWindow* mw = NULL;
ParameterManager* pm;

void * run_server(void *)  {
    cout << "Cyrus server is running ... " << endl;

    SSLReferee *referee = new SSLReferee(pm->get<int   >("network.REFEREE_PORT"),
                                         pm->get<string>("network.REFEREE_ADDRESS"));

    SSLVision *vision = new SSLVision(pm->get<int   >("network.VISION_PORT"),
                                      pm->get<string>("network.VISION_ADDRESS"));

    VisionFilter *filter =  VisionFilter::getInstance();

    SSLGame *gameModule = SSLGame::getInstance((Color)pm->get<int>("general.game.our_color"),
                                               (Side )pm->get<int>("general.game.our_side"));

    GUIHandler *gui = GUIHandler::getInstance();

    CommandTransmitter* transmitter = CommandTransmitter::getInstance();
 //   transmitter->type = CommandTransmitter::SERIAL;

    TestInput* vision_tester = new TestInput();
    TestSkills* skill_tester = new TestSkills();
    TestReferee* referee_tester = new TestReferee();

//    Test::testVelocityStrenght();
//    Test::testContactShapes();

    long loopCounter = 0;
    while ( true )
    {
        if(mw) {
            if(MainWindow::turn_off) {
                cout << "server turned off" << endl;
                exit(1);
            }
            if(MainWindow::idle_server) {
                sleep(1);
                continue;
            }
            SSLVision::setIdle(MainWindow::idle_vision);
        }
        if(loopCounter % 5 == 0)   {
//            vision_tester->updateWorldModel();
            filter->check();
            gui->check();
        }
        loopCounter ++;
        referee->check();
//        referee_tester->check();

//        vision->check(); // in thread 2
        if((loopCounter % 10) ==0) {
            analyzer->check();
            double tic = currentTimeMSec();
            gameModule->check();
            double toc = currentTimeMSec();
            double process_time = toc - tic;
//            NetworkPlotter::getInstance()->buildAndSendPacket("Process Time", process_time);
//            printf("Process Time = \t%f milli second\n", process_time);
//            transmitter->clear();
            skill_tester->testGotoPoint();

            transmitter->check();
        }
        usleep(1000);
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    app.setApplicationName("Cyrus SSL");
    app.setOrganizationName("Shahid Beheshti Computer Engineering Department");
    app.setOrganizationDomain("http://robocup.sbu.ac.ir");

    pm = ParameterManager::getInstance();

    bool gui_enabled = true;
    bool server_enabled = false;
    for(int i=0; i<argc; i++) {
        char* option_i = argv[i];
        if(!strcmp(option_i, "--help")) {
            //print help notes
            exit(1);
        }

        if(!strcmp(option_i, "--about")) {
            cout << "Application: " << app.applicationName().toStdString().c_str() << endl;
            cout << "Oganization: " << app.organizationName().toStdString().c_str() << endl;
            cout << "Web: " << app.organizationDomain().toStdString().c_str() << endl;
            exit(1);
        }

        if(!strcmp(option_i, "--gui")) {
            gui_enabled = true;
        }
        if(!strcmp(option_i, "-g")) {
            gui_enabled = true;
        }


        if(!strcmp(option_i, "--wserver")) {
            server_enabled = false;
        }
        if(!strcmp(option_i, "-ws")) {
            server_enabled = false;
        }
    }


    srand(time(0));

    QtConcurrent::run(run_server, (void*)NULL);

    gui_enabled = pm->get<bool>("general.GUI");
    if(gui_enabled) {
        mw = MainWindow::getInstance();
        mw->show();
    }

    if(gui_enabled) {
        Debugger::instance = new BuiltInDebug();
        Debugger::dbg()->print("Debugger is running ... ");
    }


    return app.exec();

}
