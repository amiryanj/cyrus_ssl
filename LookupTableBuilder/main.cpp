#include "Dialogs/designdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DesignDialog w;
    w.show();

    return a.exec();
}
