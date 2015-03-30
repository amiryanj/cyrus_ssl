#include <QApplication>
#include "mainwindow.h"
#include "plotwidget.h"
#include "selectcolordialog.h"
#include "../server/paramater-manager/parametermanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ParameterManager* pm = ParameterManager::getInstance();

//    SelectColorDialog *dialog = new SelectColorDialog;
    SSL::Color _color = (Color)pm->get<int>("general.game.our_color");
    SSL::Side  _side  = (Side)pm->get<int>("general.game.our_side");

    MainWindow* w = new MainWindow(_color, _side, 0);
    w->joinCyrusServer();

    w->show();

//    else
//        return 0;

    return a.exec();
}
