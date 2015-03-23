#include <QtGui/QApplication>
#include "mainwindow.h"

#include "../server/vision/SSLVision.h"
#include "../common/general.h"
#include "../server/paramater-manager/parametermanager.h"
#include "algorithm"
//#include ""

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    float value_array[5] = {0.11,
                            3.30,
                            0.1, 0.0, 0.4};
    std::vector<float> values;
    values.push_back(1.2);
    values.push_back(2.2);
    values.push_back(0.2);
    values.push_back(4.2);

    vector<float>::iterator x = min<std::vector<float>::iterator >(values.begin(), values.end()) ;

    ParameterManager* pm = ParameterManager::getInstance();
    SSLVision *vision = new SSLVision(pm->get<int>("network.VISION_PORT"),
                                      pm->get<string>("network.VISION_ADDRESS"));
    
    return a.exec();
}
