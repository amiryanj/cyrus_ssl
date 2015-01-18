#include "mainwindow.h"
#include <QApplication>
#include "settingmanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    SettingManager s;
    s.Save("save.json");
    return a.exec();
}
