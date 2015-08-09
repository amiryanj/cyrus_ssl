#ifndef _WATCHFIELDGRAPHICS_H
#define _WATCHFIELDGRAPHICS_H

#include <QWidget>
#include "fieldgraphicsview.h"
#include "graphics/graphic_bot.h"
#include "graphics/graphic_num.h"
#include "graphics/graphic_vec.h"
#include "graphics/graphic_plan.h"
#include "graphics/graphic_circle.h"
#include "graphics/graphic_intersect.h"
#include "graphics/graphic_ball.h"
#include "graphics/graphic_arc.h"
#include "general.h"
#include "sslnamespace.h"

#include "robotstate.h"

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

    void updateRobotState(const RobotState& st);
    void updateBallState(const BallState &st);
//    void updateRobotPlan(int id, QVector<RobotState> path, QVector3D desired_vel, QVector3D applied_vel);
//    void updateZoom(int zoom);
//    void updateCurrentStrategy(QString name, QMap<int, QString> robot_roles);
//    void updateNearestRobotToBall(int blueID,int yellowID,SSL::Color possessorTeam, bool nearestCacnKick);
//    void updateRobotIntersect(float time, RobotState st);
    
private:
    Ui::WatchFieldGraphics *ui;
    FieldGraphicsView* view;

    RobotGraphicsItem *robot[2][MAX_ID_NUM];
    NumberGraphicsItem *number[2][MAX_ID_NUM];
    VectorGraphicsItem *robotActualVel[2][MAX_ID_NUM];
    IntersectGraphicsItem *robotIntersect[2][MAX_ID_NUM];

    QPointF lastPositionMousePressed;

    PlanGraphicsItem* plan[MAX_ID_NUM];
    VectorGraphicsItem *desiredVel[MAX_ID_NUM];
    VectorGraphicsItem *appliedVel[MAX_ID_NUM];
    ArcGraphicsItem *robotRotation[MAX_ID_NUM];

    QGraphicsItem *ballZone;
    QGraphicsItem *ballIntersectionWithGoal;

    CircleGraphicsItem *ball;
    BallGraphicsItem *ballTail;
    VectorGraphicsItem *ballVel;

    int lastNearBlueID;
    int lastNearYellowID;
    bool lastNearCanKick;

    bool isShowingIntersects;
    bool isShowingPlans;

    QGraphicsScene scene;
};

#endif // _WATCHFIELDGRAPHICS_H

