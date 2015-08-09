#include "watchfieldgraphics.h"
#include "ui_watchfieldgraphics.h"
#include "general.h"
#include <QDebug>

using namespace SSL;

WatchFieldGraphics::WatchFieldGraphics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WatchFieldGraphics)
{
    ui->setupUi(this);
    view = new FieldGraphicsView(&scene, this);

    ui->mainLayout->addWidget(view);

    for(int tm=0; tm<2; tm++)
        for(int i=0; i< MAX_ID_NUM; i++)
        {
            Qt::GlobalColor robot_color = ((SSL::Color)tm == SSL::Yellow)? Qt::yellow : Qt::blue;
            robot[tm][i] = new RobotGraphicsItem(robot_color, i);
            robot[tm][i]->setZValue(2);
            scene.addItem(robot[tm][i]);

            number[tm][i] = new NumberGraphicsItem(i);
            number[tm][i]->setColor(((Color)tm == Yellow)? Qt::yellow : Qt::blue);
            number[tm][i]->setZValue(3);
//            number[tm][i]->setParentItem(robot[tm][i]);
            scene.addItem(number[tm][i]);

            RobotState rs_;
            rs_.ID = i;
            rs_.color = (Color)tm;
            updateRobotState(rs_);
        }

    ball = new CircleGraphicsItem(22, QColor(255,120,0));
    scene.addItem(ball);
    ball->setZValue(7);

    ballVel = new VectorGraphicsItem(Qt::cyan);
    ballVel->setParentItem(ball);
    ballVel->setZValue(8);

    ballTail = new BallGraphicsItem(Qt::red);
    scene.addItem(ballTail);
    ballTail->setZValue(9);


    drawBounds();    
}

WatchFieldGraphics::~WatchFieldGraphics()
{
    delete ui;
}

void WatchFieldGraphics::drawBounds()
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

void WatchFieldGraphics::updateRobotState(const RobotState &st)
{
    int team = (int)st.color;
    if(team >=2 || st.ID >= MAX_ID_NUM)
    {
        qDebug() << "invalid robot state";
        return;
    }
    robot[team][st.ID]->setPos(st.position.X(), -st.position.Y()); // ok
    robot[team][st.ID]->setRotation(-st.position.Teta() * 180.0/M_PI); // ok

    number[team][st.ID]->setPos(st.position.X(), -st.position.Y());


//    robotActualVel[team][id]->setEnd(20*st.velocity.X(), -20*st.velocity.Y());

//    if(isShowingIntersects)
//        robotIntersect[team][id]->setRobotPosition(st.position.X(),-st.position.Y());

//    if(st.color == ourColor) {
//        desiredVel[id]->setPos(st.position.X(), -st.position.Y());
//        appliedVel[id]->setPos(st.position.X(), -st.position.Y());
    //    }

}

void WatchFieldGraphics::updateBallState(const BallState &st)
{
//    qDebug()<<"ball position : "<< st.position.X() << st.position.Y();
    ball->setPos(st.position.X(), -st.position.Y());
    ballVel->setEnd(st.velocity.X(), -st.velocity.Y());
    ballTail->setNewPosition(QVector2D(st.position.X(), st.position.Y()));
}
