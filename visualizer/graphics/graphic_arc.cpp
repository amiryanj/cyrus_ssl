#include "graphic_arc.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include "../../shared/general.h"

ArcGraphicsItem::ArcGraphicsItem(QColor color)
{
    this->color = color;
    this->arcLenght = 0;
}

void ArcGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    float radius = ROBOT_RADIUS * 1.1;
    static QRectF rectangle(-radius, -radius, 2*radius, 2*radius);
    painter->setPen(QPen(color, 8));
    painter->drawArc(rectangle, 0, arcLenght * 16);
}

QRectF ArcGraphicsItem::boundingRect() const
{
    return QRectF(-ROBOT_RADIUS, -ROBOT_RADIUS, 2*ROBOT_RADIUS, 2*ROBOT_RADIUS);
}

void ArcGraphicsItem::setArcLenght(float x)
{
    this->arcLenght = x;
}


