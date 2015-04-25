#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QMap>
#include <QVector3D>
#include <QVector>
#include "robotstate.h"
#include "../shared/proto/visualizer/cpp/ssl_world.pb.h"
#include "../shared/proto/visualizer/cpp/ssl_analyzer.pb.h"
#include "../shared/proto/visualizer/cpp/ssl_decision.pb.h"
#include "../shared/proto/visualizer/cpp/ssl_planner.pb.h"

class PacketParser : public QObject
{
    Q_OBJECT

public:
    PacketParser();

signals:
    void newRobotState(RobotState state);
    void newBallState(BallState state);
    void newRobotVelocity(int id, QVector3D desired, QVector3D applied);

    void newPlan(int id, QVector<RobotState> plan, QVector3D desiredVel, QVector3D appliedVel);
    void ourColorAndSide(SSL::Color c, SSL::Side s);
    void currentStrategy(QString strategy_name, QMap<int, QString>);
    void newNearestRobotToBall(int blueID, int yellowID,SSL::Color possessorTeam, bool nearestCanKick);
    void gameRunning(bool value);
    void newIntersectPoint(float time, RobotState st);
    void newRefereeState(QString state);
    void ballIntersectionGoalLine(Vector2D intersection);

public slots:
    void handleWorldPacket(ssl_world_packet p);
    void handleDecisionPacket(ssl_decision_packet p);
    void handleAnalyzerPacket(ssl_analyzer_packet p);
    void handlePlannerPacket(ssl_planner_packet p);

};

#endif // PARSER_H
