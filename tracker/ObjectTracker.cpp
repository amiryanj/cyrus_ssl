#include <QtGui/QApplication>
#include "mainwindow.h"

#include "../shared/general.h"
#include "../server/vision/sslvision.h"
#include "../server/paramater-manager/parametermanager.h"
#include "algorithm"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ParameterManager* pm = ParameterManager::getInstance();
    SSLVision *vision = new SSLVision(pm->get<int>("network.VISION_PORT"),
                                      pm->get<string>("network.VISION_ADDRESS"));
    
    return a.exec();
}
