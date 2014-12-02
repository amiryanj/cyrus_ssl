#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QUdpSocket>
#include <QTimer>
#include "general.h"

class UdpSocket : public QObject
{
    Q_OBJECT
public:
    UdpSocket(QObject* parent = 0);
    QTimer timer;

public slots:
    bool joinNetwork(QString IP_ = "127.0.0.1", int port_ = 4001);
    void leaveNetwork();

private slots:
    void processPendingData();
    void timerTimeout();

private:
    QUdpSocket socket;
    QByteArray receivedData;
    QString _ip;
    int _port;

signals:
    void dataPacketReceived(QByteArray);

};

#endif // UDPSOCKET_H
