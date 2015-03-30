#ifndef PACKETRECEIVER_H
#define PACKETRECEIVER_H

#include "QObject"
#include "thirdparty/socket/netraw.h"
#include "thirdparty/socket/IPPacket.h"
#include "robotstate.h"
#include <QUdpSocket>
#include <QTimer>
#include "general.h"
#include "protoc/visualizer/cpp/ssl_visualizer.pb.h"
#include "protoc/visualizer/cpp/ssl_world.pb.h"
#include "protoc/visualizer/cpp/ssl_analyzer.pb.h"
#include "protoc/visualizer/cpp/ssl_decision.pb.h"
#include "protoc/visualizer/cpp/ssl_planner.pb.h"

class PacketReceiver : public QObject
{
    Q_OBJECT
public:
    PacketReceiver();
    ~PacketReceiver();
    QTimer timer;

public slots:
    void setNetworkSettings(int port, QString address);
    bool joinNetwork();
    void disconnectNetwork();

private slots:
    void processPendingData();
    void timerTimeout();


private:
      QUdpSocket socket;
      QByteArray receivedData;

      ssl_visualizer_packet vis_packet;
      QString mAddress;
      int mPort;

signals:
      void newWorldPacket(ssl_world_packet packet);
      void newAnalyzerPacket(ssl_analyzer_packet packet);
      void newDecisionPacket(ssl_decision_packet packet);
      void newPlannerPacket(ssl_planner_packet packet);
};

#endif // PACKETRECEIVER_H
