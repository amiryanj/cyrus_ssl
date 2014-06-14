#include "graphic_vec.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

VectorGraphicsItem::VectorGraphicsItem(Qt::GlobalColor color)
{
    this->color = color;
}

void VectorGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(globalOrien)
        this->setRotation(-this->parentItem()->rotation());
    painter->setPen(QPen(color, 7));
    painter->drawLine(QPointF(0,0), end);
}

QRectF VectorGraphicsItem::boundingRect() const
{
    return QRectF(QPointF(0,0), end);
}

void VectorGraphicsItem::setEnd(double x, double y)
{
    this->end.setX(x/10);
    this->end.setY(y/10);
    //    qDebug() << "V_x = " << x << " , V_y = " << y;
}

void VectorGraphicsItem::setGlobalOrien(bool g)
{
    this->globalOrien = g;
}


