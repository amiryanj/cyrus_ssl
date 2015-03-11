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

        painter->setPen(Qt::red);
        painter->setBrush(QColor(200,0,0,100));
        QPolygon poly;
        poly.append(QPoint(0,0));
        poly.append(QPoint(FIELD_LENGTH/2-this->x(),-FIELD_GOAL_WIDTH/2-this->y()));
        poly.append(QPoint(FIELD_LENGTH/2-this->x(),FIELD_GOAL_WIDTH/2-this->y()));
        painter->drawPolygon(poly);
        painter->setBrush(QColor(0,0,200,100));
        poly.clear();
        poly.append(QPoint(0,0));
        poly.append(QPoint(-FIELD_LENGTH/2-this->x(),-FIELD_GOAL_WIDTH/2-this->y()));
        poly.append(QPoint(-FIELD_LENGTH/2-this->x(),FIELD_GOAL_WIDTH/2-this->y()));
        painter->drawPolygon(poly);


        painter->setPen(QColor(255,120,0));
        painter->setBrush(myColor);
        painter->drawEllipse(-myRadius, -myRadius, myRadius*2, myRadius*2);
}

QRectF CircleGraphicsItem::boundingRect() const
{
    return QRect(-FIELD_LENGTH/2,-FIELD_WIDTH/2,FIELD_LENGTH,FIELD_WIDTH);
    //return QRect(-myRadius, -myRadius, 2*myRadius, 2*myRadius);
}
