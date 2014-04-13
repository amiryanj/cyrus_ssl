#ifndef FIELDSCENE_H
#define FIELDSCENE_H

#include <QWidget>
#include <QGraphicsView>
#include "graphics/graphic_bot.h"
#include "graphics/graphic_num.h"
#include "graphics/graphic_vec.h"
#include "graphics/graphic_plan.h"
#include "graphics/graphic_circle.h"
#include "graphics/graphic_intersect.h"
#include "Concepts.h"
#include "robotstate.h"
#include <QWheelEvent>

namespace Ui {
class FieldScene;
}
using namespace SSL;
class FieldScene : public QWidget
{
    Q_OBJECT
    
public:

    void setIsShowingIntersects(bool show);
    void setIsShowingPlans(bool show);

    explicit FieldScene(SSL::Color our_color, QWidget *parent = 0);
    ~FieldScene();
    SSL::Color ourColor; // just should be set by mainwindow

    void wheelEvent(QWheelEvent *);

signals:

    void zoomWheel(int);


public slots:
//    void updateRobotState(Color c, int id, const RobotState& st);
    void updateRobotState(const RobotState& st);
    void updateBallState(const BallState &st);
    void updateRobotPlan(int id, QVector<RobotState> path, QVector3D desired_vel, QVector3D applied_vel);
    void updateZoom(int zoom);
    void updateCurrentStrategy(QString name, QMap<int, QString> robot_roles);
    void updateNearestRobotToBall(int blueID,int yellowID,SSL::Color possessorTeam, bool nearestCacnKick);
    void updateRobotIntersect(float time, RobotState st);
    
private:
    Ui::FieldScene *ui;
    RobotGraphicsItem *robot[2][MAX_ID_NUM];
    NumberGraphicsItem *number[2][MAX_ID_NUM];
    VectorGraphicsItem *robotActualVel[2][MAX_ID_NUM];
    IntersectGraphicsItem *robotIntersect[2][MAX_ID_NUM];

    PlanGraphicsItem* plan[MAX_ID_NUM];
    VectorGraphicsItem *desiredVel[MAX_ID_NUM];
    VectorGraphicsItem *appliedVel[MAX_ID_NUM];


    CircleGraphicsItem *ball;
    VectorGraphicsItem *ballVel;

    int lastNearBlueID;
    int lastNearYellowID;
    bool lastNearCanKick;

    bool isShowingIntersects;
    bool isShowingPlans;

    QGraphicsScene scene;

    void drawBounds();
};

#endif // FIELDSCENE_H
