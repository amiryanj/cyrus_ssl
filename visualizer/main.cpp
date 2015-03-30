#include <QApplication>
#include "mainwindow.h"
#include "plotwidget.h"
#include "selectcolordialog.h"
#include "../server/paramater-manager/parametermanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow* w;
    ParameterManager* pm = ParameterManager::getInstance();

    SelectColorDialog *dialog = new SelectColorDialog;
    if(dialog->exec() == QDialog::Accepted)  {
        w = new MainWindow(dialog->getOurColor(), dialog->getOurSide(), 0);
        if(!w->joinCyrusServer())  {
            dialog->setStatusText("Couldn't connect to Cyrus Server");
//            sleep(2);
        }


        w->show();
//        w->showFullScreen();
    }
    else
        return 0;

    return a.exec();
}
