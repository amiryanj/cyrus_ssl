#ifndef _PACKETRECEIVER_H
#define _PACKETRECEIVER_H

#include <QUdpSocket>
#include <QTimer>
#include "robotstate.h"
#include "../shared/proto/visualizer/cpp/ssl_visualizer.pb.h"
#include "../shared/proto/visualizer/cpp/ssl_world.pb.h"
#include "../shared/proto/visualizer/cpp/ssl_analyzer.pb.h"
#include "../shared/proto/visualizer/cpp/ssl_decision.pb.h"
#include "../shared/proto/visualizer/cpp/ssl_planner.pb.h"

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
