#ifndef _WATCHFIELDGRAPHICS_H
#define _WATCHFIELDGRAPHICS_H

#include <QWidget>
#include "fieldgraphicsview.h"

#include <QGraphicsScene>

namespace Ui {
class WatchFieldGraphics;
}

class WatchFieldGraphics : public QWidget
{
    Q_OBJECT
    
public:
    explicit WatchFieldGraphics(QWidget *parent = 0);
    ~WatchFieldGraphics();

public slots:
    void drawBounds();

//    void updateRobotState(const RobotState& st);
//    void updateBallState(const BallState &st);
//    void updateRobotPlan(int id, QVector<RobotState> path, QVector3D desired_vel, QVector3D applied_vel);
//    void updateZoom(int zoom);
//    void updateCurrentStrategy(QString name, QMap<int, QString> robot_roles);
//    void updateNearestRobotToBall(int blueID,int yellowID,SSL::Color possessorTeam, bool nearestCacnKick);
//    void updateRobotIntersect(float time, RobotState st);
    
private:
    Ui::WatchFieldGraphics *ui;
    FieldGraphicsView* view;

    QGraphicsScene scene;
};

#endif // _WATCHFIELDGRAPHICS_H


/*
#ifndef FIELDGRAPHIC_H
#define FIELDGRAPHIC_H

#include <QWidget>
#include <QGraphicsScene>
#include <QVector3D>
#include <QVector2D>
#include "tools/vector3d.h"
#include "fieldview.h"
#include "planning/obstacle.h"
#include "graphic_items/graphic_car.h"
#include "graphic_items/graphic_plan.h"
#include "graphic_items/graphic_laser.h"
#include "graphic_items/graphic_tail.h"

namespace Ui {
class FieldGraphic;
}

class FieldGraphic : public QWidget
{
    Q_OBJECT

public:
    explicit FieldGraphic(QWidget *parent = 0);
    ~FieldGraphic();

public slots:
    void updateAgentPosition(QVector3D position);
    void updateAgentTarget(Vector3D carTarget);
    void drawObstacle(Obstacle *ob, QColor color = Qt::gray, int dynamic_id = 0);
    void drawRoads();
    void drawPlan(Trajectory &carPlan, bool connectThem, QColor color, bool clearOtherPlans = true);
    void drawRRTTree(Trajectory &tree, QColor color = Qt::yellow);
    void drawForces(QVector2D pnt, QVector<QVector2D> forces);
    void setZoom(float z);
    void updateLaserData(QVector<float> data_);
    void updateLaserData(QVector<QLineF> lines_);
    void clearObstacles();


signals:
    void targetUpdatedByDrag(QVector3D new_target);

private:
    static const int carObstacleCount = 10;
    QVector<QGraphicsItem*> forces_items;
    Ui::FieldGraphic *ui;
    QGraphicsScene scene;

    CarGraphicsItem* carObstacles[carObstacleCount];
    TailGraphicsItem* obstacleTail[carObstacleCount];

    QVector<QGraphicsItem*> drawnObstacles;
    QVector<QGraphicsItem*> drawnStreetMidlines;
    QVector<QGraphicsItem*> drawnRoads;

    FieldView *view;

    CarGraphicsItem *car;
    CarGraphicsItem *carTarget;
    TailGraphicsItem* carTail;

    PlanGraphicsItem *carPlan;
    QVector<PlanGraphicsItem*> plan_list;
    PlanGraphicsItem *rrtTree;
    LaserGraphicsItem *laser;
};

#endif // FIELDGRAPHIC_H
*/
