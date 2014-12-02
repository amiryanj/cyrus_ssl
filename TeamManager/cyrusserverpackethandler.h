#ifndef _CYRUSSERVERPACKETHANDLER_H
#define _CYRUSSERVERPACKETHANDLER_H

#include <QObject>
#include "udpsocket.h"

class CyrusServerPacketHandler : public QObject
{
    Q_OBJECT
public:
    explicit CyrusServerPacketHandler(QObject* parent = 0);

private:
    UdpSocket socket;

private slots:
    void processCyrusPacket(QByteArray data_);
};

#endif // _CYRUSSERVERPACKETHANDLER_H
