#include "graphic_plan.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include "../../shared/general.h"

PlanGraphicsItem::PlanGraphicsItem(Qt::GlobalColor color)
{
    myColor = color;
    myRadius = 60;
}

void PlanGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    for(int i=0; i<path.size() - 1; i++) {
        if(i==0) {  // init state
            painter->setPen(Qt::green);
        }
        else {
            painter->setPen(Qt::magenta);
        }

        QVector3D state= path.at(i);
        QVector3D next_state = path.at(i+1);
        painter->drawChord(-myRadius +state.x(), -myRadius-state.y(), myRadius*2,myRadius*2,
                            16*(state.z()*180/M_PI + 40), 16 * 280);
        painter->setPen(Qt::black);
        painter->drawLine(QPoint(state.x(), -state.y()), QPoint(next_state.x(), -next_state.y()));
    }

    if(!path.empty()) { // drawing goal_state
        painter->setPen(QPen(Qt::darkYellow, 10));
        QVector3D goal = path.last(); // goal state
        painter->drawChord(-ROBOT_RADIUS +goal.x(), -ROBOT_RADIUS-goal.y(), ROBOT_RADIUS*2, ROBOT_RADIUS*2,
                           16*(goal.z()*180/M_PI + 40), 16*280);
    }
//        painter->setPen(myColor);
//        foreach (QVector3D state, this->path) {
//            painter->drawChord(-myRadius +state.x(), -myRadius-state.y(),myRadius*2,myRadius*2,
//                               16*(state.z()*180/M_PI + 40), 16*280);
//        }
        this->setOpacity(0.7);
    path.clear();
}

QRectF PlanGraphicsItem::boundingRect() const
{
    return QRect(-FIELD_LENGTH/2,-FIELD_WIDTH/2,FIELD_LENGTH,FIELD_WIDTH);
}

void PlanGraphicsItem::setPath(QVector<QVector3D> p)
{
    this->path = p;
}

void PlanGraphicsItem::clearPath()
{
    this->path.clear();
}
