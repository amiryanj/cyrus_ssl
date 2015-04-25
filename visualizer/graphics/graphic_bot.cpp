#include "graphic_bot.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include "../../shared/general.h"

RobotGraphicsItem::RobotGraphicsItem(Qt::GlobalColor color, int id)
{
    myMode = RobotGraphicMode;
    myColor = color;
    myID = id;
    myRadius = 90;
    isNearest = false;
    IsTotalNearest = false;
    canKick = false;
}

RobotGraphicsItem::RobotGraphicsItem(Mode mode, int itsDimension)
{
    this->myMode = mode;
    this->myRadius = itsDimension;
}

void RobotGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->setClipRect(boundingRect());
    if(this->myMode==RobotGraphicMode)
    {
        if(this->isNearest == true)
        {
            QPen pen(QColor(178,34,34));
            pen.setWidth(15);
            painter->setPen(pen);
            painter->setBrush(Qt::transparent);
            painter->drawEllipse(-(myRadius+30),-(myRadius+30),(myRadius+30)*2,(myRadius+30)*2);
            painter->setPen(myColor);
        }
        if(this->IsTotalNearest == true)
        {
            QPen pen(Qt::red);
            pen.setWidth(15);
            painter->setPen(pen);
            painter->setBrush(QColor(Qt::transparent));
            painter->drawEllipse(-(myRadius+30),-(myRadius+30),(myRadius+30)*2,(myRadius+30)*2);
            painter->setPen(myColor);

        }

        if(this->canKick) {
            QPen pen(QColor(Qt::darkCyan));
            pen.setWidth(10);
            painter->setPen(pen);
            painter->setBrush(QColor(Qt::transparent));
            painter->drawRect(-(myRadius+50),-(myRadius+50),(myRadius+50)*2,(myRadius+50)*2);
            painter->setPen(myColor);
        }
        painter->setPen(myColor);
        painter->setBrush((myColor==Qt::blue)? QColor(Qt::blue):QColor(Qt::yellow));
        painter->drawChord(-myRadius,-myRadius,myRadius*2,myRadius*2,35*16,290*16);
        painter->setPen((this->myColor==Qt::blue)? QColor(200,200,255):QColor(150,150,170));
        painter->drawLine(40,0,74,0);
    }

    else if(this->myMode==RobotTargetGraphicMode)
    {
        painter->setPen((this->myColor==Qt::blue)? QColor(Qt::blue):QColor(Qt::yellow));
        painter->setBrush((this->myColor==Qt::blue)? QColor(Qt::blue):QColor(Qt::yellow));
        painter->drawChord(-myRadius,-myRadius,myRadius*2,myRadius*2,35*16,290*16);
        painter->drawLine(40,0,74,0);
    }
}

QRectF RobotGraphicsItem::boundingRect() const
{
    return QRect(-FIELD_LENGTH/2,-FIELD_WIDTH/2,FIELD_LENGTH,FIELD_WIDTH);
}
void RobotGraphicsItem::setNearest(bool nearest)
{
    isNearest = nearest;
}

void RobotGraphicsItem::setTotalNearest(bool nearest)
{
    IsTotalNearest = nearest;
}

void RobotGraphicsItem::setCanKick(bool can_kick)
{
    canKick = can_kick;
}
