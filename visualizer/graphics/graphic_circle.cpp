#include "graphic_circle.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

CircleGraphicsItem::CircleGraphicsItem(int radius, QColor color, int id)
{
    myRadius = radius;
    myColor = color;
    myID = id;
}

void CircleGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->setPen(QColor(255,120,0));
        painter->setBrush(myColor);
        painter->drawEllipse(-myRadius, -myRadius, myRadius*2, myRadius*2);
}

QRectF CircleGraphicsItem::boundingRect() const
{
    return QRect(-myRadius, -myRadius, 2*myRadius, 2*myRadius);
}
