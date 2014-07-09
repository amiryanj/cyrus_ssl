#include "fieldscene.h"
#include "ui_fieldscene.h"
#include <QDebug>
#include <QVector3D>

FieldScene::FieldScene(Color our_color, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FieldScene)
{
    ourColor = our_color;
    ui->setupUi(this);
    for(int tm=0; tm<2; tm++)
        for(int i=0; i< MAX_ID_NUM; i++)
        {
            Qt::GlobalColor robot_color = ((Color)tm == Yellow)? Qt::yellow:Qt::blue;
            robot[tm][i] = new RobotGraphicsItem(robot_color, i);
            scene.addItem(robot[tm][i]);
            robot[tm][i]->setZValue(2);

            number[tm][i] = new NumberGraphicsItem(i);
            number[tm][i]->setColor(((Color)tm == Yellow)? Qt::yellow:Qt::blue);
            number[tm][i]->setZValue(3);
            number[tm][i]->setParentItem(robot[tm][i]);
//            scene.addItem(number[tm][i]);

            robotActualVel[tm][i] = new VectorGraphicsItem(Qt::green);
//            robotActualVel[tm][i]->setParentItem(robot[tm][i]);
            robotActualVel[tm][i]->setZValue(4);
            robotActualVel[tm][i]->setGlobalOrien(true);



            robotIntersect[tm][i] = new IntersectGraphicsItem();
          //  robotIntersect[tm][i]->setParentItem(robot[tm][i]);
            robotIntersect[tm][i]->setZValue(5);
            scene.addItem(robotIntersect[tm][i]);


            if(tm==(int)ourColor) // just for our team
            {
                plan[i] = new PlanGraphicsItem(Qt::magenta);
                plan[i]->setZValue(1.5);
                scene.addItem(plan[i]);

                desiredVel[i] = new VectorGraphicsItem(Qt::magenta);
                desiredVel[i]->setParentItem(robot[tm][i]);
                desiredVel[i]->setZValue(5);
                desiredVel[i]->setGlobalOrien(true);

                appliedVel[i] = new VectorGraphicsItem(Qt::red);
//                scene.addItem(appliedVel[i]);
                appliedVel[i]->setParentItem(robot[tm][i]);
                appliedVel[i]->setZValue(6);
                appliedVel[i]->setGlobalOrien(false);

            }

            RobotState st((Color)tm, i);
            int side = (tm*2) - 1;
            st.position = Vector3D(side * (i+2) * 200, side * (FIELD_WIDTH/2 + 400), side * M_PI_2);
            updateRobotState(st);
        }

    ball = new CircleGraphicsItem(22, QColor(255,120,0));
    scene.addItem(ball);
    ball->setZValue(7);

    ballTail = new BallGraphicsItem(Qt::red);
    scene.addItem(ballTail);
    ballTail->setZValue(9);

    ballVel = new VectorGraphicsItem(Qt::cyan);
    ballVel->setParentItem(ball);
    ballVel->setZValue(8);

    drawBounds();

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->scale(0.08, 0.08);

    connect(this, SIGNAL(zoomWheel(int)), this, SLOT(updateZoom(int)));
   // connect(ui->verticalSlider,SIGNAL(valueChanged(int)),this,SLOT(updateZoom(int)));

    this->lastNearBlueID = 0;
    this->lastNearYellowID = 0;
    this->lastNearCanKick = false;

    isShowingIntersects = false;
    isShowingPlans = false;



}

FieldScene::~FieldScene()
{
    delete ui;
}

void FieldScene::wheelEvent(QWheelEvent * wheelEvent)
{
    emit zoomWheel(wheelEvent->delta());
}
void FieldScene::setIsShowingIntersects(bool show)
{
    isShowingIntersects = show;
}

void FieldScene::setIsShowingPlans(bool show)
{
    isShowingPlans = show;
}


void FieldScene::updateRobotState(const RobotState &st)
{
    int team = (int)st.color;
    int id = st.ID;
    if(team >=2 || id >= MAX_ID_NUM)
    {
        qDebug() << "invalid robot state";
        return;
    }
    robot[team][id]->setPos(st.position.X(), -st.position.Y()); // ok
    robot[team][id]->setRotation(-st.position.Teta() * 180/M_PI); // ok

    robotActualVel[team][id]->setEnd(20*st.velocity.X(), -20*st.velocity.Y());

    if(isShowingIntersects)
        robotIntersect[team][id]->setRobotPosition(st.position.X(),-st.position.Y());

}

void FieldScene::updateBallState(const BallState &st)
{
    qDebug()<<"ball position : "<< st.position.X() << st.position.Y();
    this->ball->setPos(st.position.X(), -st.position.Y());
    this->ballVel->setEnd(st.velocity.X(), -st.velocity.Y());

    ballTail->setNewPosition(QVector2D(st.position.X(), st.position.Y()));

}

void FieldScene::updateRobotPlan(int id, QVector<RobotState> path, QVector3D desired_vel, QVector3D applied_vel)
{
    QVector<QVector3D> pathToShow;
    foreach (RobotState state, path) {
        QVector3D pos(state.position.X(), state.position.Y(), state.position.Teta());
        pathToShow.append(pos);
    }
    if(id <0 || id>=MAX_ID_NUM)  {
        qErrnoWarning("Error: invalid id for planner");
        return;
    }
    if(isShowingPlans)
    {
        plan[id]->setPath(pathToShow);
    }

    desiredVel[id]->setEnd(desired_vel.x(), -desired_vel.y());
    appliedVel[id]->setEnd(applied_vel.x(), -applied_vel.y());
    //    appliedVel[id]->setPos(robot[ourColor][id]->pos().x(), -robot[ourColor][id]->pos().y());
//    appliedVel[id]->rotate(-appliedVel[id]->parentItem()->rotation());
//    appliedVel[id]->setPos(robot[ourColor][id]->x(), -robot[ourColor][id]->y());
}

void FieldScene::updateZoom(int zoom)
{
    static double zoomPercent = 0.07;
    if(zoom > 0)
        zoomPercent += 0.01;
    else
        zoomPercent -= 0.01;

    QTransform t;
    t.scale(zoomPercent, zoomPercent);
    ui->graphicsView->setTransform(t);
    //    ui->graphicsView->scale(zoomPercent, zoomPercent);
}

void FieldScene::updateCurrentStrategy(QString name, QMap<int, QString> robot_roles)
{
    foreach (int id, robot_roles.keys()) {
        number[ourColor][id]->setText(robot_roles.value(id));
    }
}

void FieldScene::updateNearestRobotToBall(int blueID, int yellowID, Color possessorTeam, bool nearestCacnKick)
{
    qDebug() << "in update : " << "blue ID :" << blueID <<"yellow ID:" << yellowID <<" total : " <<possessorTeam;


    robot[Blue][lastNearBlueID]->setNearest(false);
    robot[Yellow][lastNearYellowID]->setNearest(false);
    robot[Blue][lastNearBlueID]->setTotalNearest(false);
    robot[Yellow][lastNearYellowID]->setTotalNearest(false);
    if(lastNearCanKick) {
        robot[Blue][lastNearBlueID]->setCanKick(false);
        robot[Yellow][lastNearYellowID]->setCanKick(false);
    }

    this->lastNearBlueID = blueID;
    this->lastNearYellowID = yellowID;
    this->lastNearCanKick = nearestCacnKick;

    robot[Blue][lastNearBlueID]->setNearest(true);
    robot[Yellow][lastNearYellowID]->setNearest(true);
    if(possessorTeam == Blue) {
        robot[Blue][lastNearBlueID]->setTotalNearest(true);
        robot[Blue][lastNearBlueID]->setCanKick(nearestCacnKick);
    }
    else if(possessorTeam == Yellow){
        robot[Yellow][lastNearYellowID]->setTotalNearest(true);
        robot[Yellow][lastNearYellowID]->setCanKick(nearestCacnKick);
    }

//    static int previousBlueID = -1,previousYellowID = -1,previousPossessorTeam = -2;
//    if(previousBlueID == -1 || previousYellowID == -1 || previousPossessorTeam == -2)
//    {
//        if(robot[Blue][blueID] != NULL)
//        {
//            robot[Blue][blueID]->setNearest(true);
//            if(possessorTeam = Blue )
//                 robot[Blue][blueID]->setTotalNearest(true);
//        }
//        if(robot[Yellow][yellowID])
//        {
//            robot[Yellow][yellowID]->setNearest(true);
//            if(possessorTeam = Yellow)
//                 robot[Yellow][yellowID]->setTotalNearest(true);
//        }
//        previousBlueID = blueID;
//        previousYellowID = yellowID;
//        previousPossessorTeam = possessorTeam;
//        return;
//    }
//    if(previousBlueID != blueID)
//    {
//        if(robot[Blue][blueID] != NULL && robot[Blue][previousBlueID] != NULL)
//        {
//            robot[Blue][blueID]->setNearest(true);
//            robot[Blue][previousBlueID]->setNearest(false);
//        }
//    }
//    if(previousYellowID != yellowID)
//    {
//        if(robot[Yellow][yellowID] != NULL && robot[Yellow][previousYellowID] != NULL)
//        {
//            robot[Yellow][yellowID]->setNearest(true);
//            robot[Yellow][previousYellowID]->setNearest(false);
//        }
//    }
//    if(previousPossessorTeam != possessorTeam)
//    {
//        robot[Yellow][yellowID]->setTotalNearest(false);
//        robot[Blue][blueID]->setTotalNearest(false);
//        robot[Yellow][previousYellowID]->setTotalNearest(false);
//        robot[Blue][previousBlueID]->setTotalNearest(false);
//    }
//    if(possessorTeam == None)
//    {
//        robot[Yellow][yellowID]->setTotalNearest(false);
//        robot[Blue][blueID]->setTotalNearest(false);
//        robot[Yellow][previousYellowID]->setTotalNearest(false);
//        robot[Blue][previousBlueID]->setTotalNearest(false);
//    }
//    else if(possessorTeam == Blue)
//    {
//        qDebug()<<"*****************************************************";
//        robot[Blue][previousBlueID]->setTotalNearest(false);
//        robot[Blue][blueID]->setTotalNearest(true);
//        if(nearestCacnKick) {

//        }
//    }
//    else if(possessorTeam == Yellow)
//    {
//        robot[Yellow][previousYellowID]->setTotalNearest(false);
//        robot[Yellow][yellowID]->setTotalNearest(true);
//    }
//    previousYellowID = yellowID;
//    previousBlueID = blueID;
//    previousPossessorTeam = possessorTeam;
}

void FieldScene::updateRobotIntersect(float time, RobotState st)
{
    int team = (int)st.color;
    int id = st.ID;
    if(team >=2 || id >= MAX_ID_NUM)
    {
        qDebug() << "invalid robot state";
        return;
    }
    for(int i = 0 ; i < MAX_ID_NUM ; i++)
        robotIntersect[team][id]->isInvisible = false;
    if(isShowingIntersects)
    {
        robotIntersect[team][id]->isInvisible = true;
        robotIntersect[team][id]->setPos(st.position.X(),-st.position.Y());
    }
}

void FieldScene::drawBounds()
{
    double FIELD_MAIN_LENGHT = 7400;
    double FIELD_MAIN_WIDTH = 5400;
    scene.setSceneRect(-FIELD_MAIN_LENGHT/2, -FIELD_MAIN_WIDTH/2, FIELD_MAIN_LENGHT, FIELD_MAIN_WIDTH);
//    scene.setSceneRect(-FIELD_MAIN_LENGHT/2, -FIELD_MAIN_WIDTH/2, FIELD_MAIN_LENGHT, FIELD_MAIN_WIDTH);

    scene.addRect(-FIELD_MAIN_LENGHT/2, -FIELD_MAIN_WIDTH/2,
                  FIELD_MAIN_LENGHT, FIELD_MAIN_WIDTH,QPen(Qt::green),QBrush(Qt::green));

    QPen drawBoundsPen(Qt::white);
    scene.addLine(-FIELD_LENGTH/2, -FIELD_WIDTH/2, -FIELD_LENGTH/2, FIELD_WIDTH/2, drawBoundsPen);
    scene.addLine(FIELD_LENGTH/2, -FIELD_WIDTH/2, FIELD_LENGTH/2, FIELD_WIDTH/2, drawBoundsPen);
    scene.addLine(-FIELD_LENGTH/2, -FIELD_WIDTH/2, FIELD_LENGTH/2, -FIELD_WIDTH/2, drawBoundsPen);
    scene.addLine(-FIELD_LENGTH/2, FIELD_WIDTH/2, FIELD_LENGTH/2, FIELD_WIDTH/2, drawBoundsPen);

    // half-field line
    scene.addLine(0, -FIELD_WIDTH/2, 0, FIELD_WIDTH/2, drawBoundsPen);
    scene.addEllipse(-FIELD_CENTER_RADIUS, -FIELD_CENTER_RADIUS, FIELD_CENTER_RADIUS*2, FIELD_CENTER_RADIUS*2, drawBoundsPen);

    QPainterPath leftPenaltyArea;
    leftPenaltyArea.moveTo(-FIELD_LENGTH/2, -FIELD_PENALTY_AREA_RADIUS - FIELD_PENALTY_AREA_WIDTH/2);
    leftPenaltyArea.arcTo(-FIELD_LENGTH/2 - FIELD_PENALTY_AREA_RADIUS, -FIELD_PENALTY_AREA_WIDTH/2-FIELD_PENALTY_AREA_RADIUS,
                       2*FIELD_PENALTY_AREA_RADIUS,2*FIELD_PENALTY_AREA_RADIUS,90,-90);
    leftPenaltyArea.arcTo(-FIELD_LENGTH/2-FIELD_PENALTY_AREA_RADIUS,FIELD_PENALTY_AREA_WIDTH/2-FIELD_PENALTY_AREA_RADIUS,
                       2*FIELD_PENALTY_AREA_RADIUS,2*FIELD_PENALTY_AREA_RADIUS,0,-90);
    scene.addPath(leftPenaltyArea, drawBoundsPen);

    QPainterPath Goal1;
    Goal1.moveTo(-FIELD_LENGTH/2,-FIELD_GOAL_WIDTH/2);
    Goal1.lineTo(-FIELD_LENGTH/2-180,-FIELD_GOAL_WIDTH/2);
    Goal1.lineTo(-FIELD_LENGTH/2-180,FIELD_GOAL_WIDTH/2);
    Goal1.lineTo(-FIELD_LENGTH/2,FIELD_GOAL_WIDTH/2);
    scene.addPath(Goal1,QPen(QColor(Qt::black),20));

    QPainterPath rightPenaltyArea;
    rightPenaltyArea.moveTo(FIELD_LENGTH/2, -FIELD_PENALTY_AREA_RADIUS - FIELD_PENALTY_AREA_WIDTH/2);
    rightPenaltyArea.arcTo(FIELD_LENGTH/2 - FIELD_PENALTY_AREA_RADIUS, -FIELD_PENALTY_AREA_WIDTH/2-FIELD_PENALTY_AREA_RADIUS,
                       2*FIELD_PENALTY_AREA_RADIUS,2*FIELD_PENALTY_AREA_RADIUS,90,90);
    rightPenaltyArea.arcTo(FIELD_LENGTH/2-FIELD_PENALTY_AREA_RADIUS,FIELD_PENALTY_AREA_WIDTH/2-FIELD_PENALTY_AREA_RADIUS,
                       2*FIELD_PENALTY_AREA_RADIUS,2*FIELD_PENALTY_AREA_RADIUS,180,90);
    scene.addPath(rightPenaltyArea, drawBoundsPen);

    QPainterPath Goal2;
    Goal2.moveTo(FIELD_LENGTH/2,-FIELD_GOAL_WIDTH/2);
    Goal2.lineTo(FIELD_LENGTH/2+180,-FIELD_GOAL_WIDTH/2);
    Goal2.lineTo(FIELD_LENGTH/2+180,FIELD_GOAL_WIDTH/2);
    Goal2.lineTo(FIELD_LENGTH/2,FIELD_GOAL_WIDTH/2);
    scene.addPath(Goal2,QPen(QColor(Qt::black),20));

}
