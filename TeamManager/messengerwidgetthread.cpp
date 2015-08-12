#include "messengerwidgetthread.h"
#include "messengerwidget.h"
#include <QDebug>
MessengerWidgetThread::MessengerWidgetThread(QObject *parent) :
    QThread(parent)
{


}
void MessengerWidgetThread::run()
{
  //  qDebug()<<"MY"<<currentThreadId();
    MSG = new MessengerWidget;
    exec();
}
