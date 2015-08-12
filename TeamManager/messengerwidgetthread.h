#ifndef MESSENGERWIDGETTHREAD_H
#define MESSENGERWIDGETTHREAD_H

#include <QThread>
#include "messengerwidget.h"
class MessengerWidgetThread : public QThread
{
    Q_OBJECT
public:
    MessengerWidget * MSG;
    explicit MessengerWidgetThread(QObject *parent = 0);
    void run();
signals:

public slots:

};

#endif // MESSENGERWIDGETTHREAD_H
