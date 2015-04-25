#include "graphic_vec.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include "../../shared/general.h"

VectorGraphicsItem::VectorGraphicsItem(Qt::GlobalColor color)
{
    this->color = color;
}

void VectorGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    if(globalOrien)
//        this->setRotation(-this->parentItem()->rotation());
    painter->setPen(QPen(color, 15));
    painter->drawLine(QPointF(0,0), end);
}

QRectF VectorGraphicsItem::boundingRect() const
{
    return QRectF(QPointF(0,0), end);
}

void VectorGraphicsItem::setEnd(double x, double y)
{
    this->end.setX(x/2);
    this->end.setY(y/2);
    //    qDebug() << "V_x = " << x << " , V_y = " << y;
}

void VectorGraphicsItem::setGlobalOrien(bool g)
{
    this->globalOrien = g;
}


