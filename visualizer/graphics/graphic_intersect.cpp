#include "graphic_intersect.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

IntersectGraphicsItem::IntersectGraphicsItem()
{
    robotPosition.set(0 , 0);
    isInvisible = false;
}
QRectF IntersectGraphicsItem::boundingRect() const
{
    return QRect(-FIELD_LENGTH/2,-FIELD_WIDTH/2,FIELD_LENGTH,FIELD_WIDTH);
}

void IntersectGraphicsItem::setRobotPosition(double x, double y)
{
    robotPosition.set(x,y);
}
void IntersectGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(isInvisible)
    {
        painter->setPen(QPen(Qt::red));
        painter->drawLine(-30,-(+30),+30,-(-30));
        painter->drawLine(+30,-(+30),-30,-(-30));
        painter->drawLine(robotPosition.X()-this->pos().x(),(robotPosition.Y()-this->pos().y()),0,0);
    }
}
