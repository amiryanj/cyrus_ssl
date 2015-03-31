#include <QApplication>
#include "mainwindow.h"
#include "plotwidget.h"
#include "selectcolordialog.h"
#include "../server/paramater-manager/parametermanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationName("Cyrus Robotics");
    app.setOrganizationDomain("robocup.sbu.ac.ir");
    app.setApplicationName("Cyrus-Visualizer");

    ParameterManager* pm = ParameterManager::getInstance();

    SSL::Color _color = (Color)pm->get<int>("general.game.our_color");
    SSL::Side  _side  = (Side)pm->get<int>("general.game.our_side");

    MainWindow* w = new MainWindow(_color, _side, 0);
    w->joinCyrusServer();

    w->showFullScreen();

    return app.exec();
}
