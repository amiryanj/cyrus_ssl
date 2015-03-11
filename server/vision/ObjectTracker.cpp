#include <QtGui/QApplication>
#include "mainwindow.h"

#include "SSLVision.h"
#include "../../common/general.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    SSLVision* vision = new SSLVision(10045, GRSIM_VISION_ADDRESS);
    
    return a.exec();
}
