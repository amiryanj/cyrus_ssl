#include "udpsocket.h"

UdpSocket::UdpSocket(QObject *parent)
    : QObject(parent)
{
    connect(&socket, SIGNAL(readyRead()), this, SLOT(processPendingData()));

    timer.setInterval(3000);
    timer.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));

}

bool UdpSocket::joinNetwork(QString IP_, int port_)
{
    _ip = IP_;
    _port = port_;

    socket.close();
    socket.bind(QHostAddress(_ip), QUdpSocket::ShareAddress);
    return socket.joinMulticastGroup(QHostAddress(_port));
}

void UdpSocket::leaveNetwork()
{
    socket.close();
}

void UdpSocket::processPendingData()
{
    qDebug() << "new data packet received";
    while (socket.hasPendingDatagrams())
    {
        receivedData.resize(socket.pendingDatagramSize());
        socket.readDatagram(receivedData.data(), receivedData.size());
    }

    timer.start();

    emit dataPacketReceived(receivedData);
}


void UdpSocket::timerTimeout()
{
    joinNetwork(_ip, _port);
    timer.start();
}
