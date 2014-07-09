#include "graphic_ball.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

BallGraphicsItem::BallGraphicsItem(Qt::GlobalColor color)
{
    myColor = color;
    myRadius = 30;
}

void BallGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(int i=0; i<path.size(); i++) {
        painter->setPen(myColor);
        this->setOpacity(0.3);
        painter->drawEllipse(path[i].toPoint(), myRadius,myRadius);
    }
//    path.clear();
}

QRectF BallGraphicsItem::boundingRect() const
{
    return QRect(-FIELD_LENGTH/2,-FIELD_WIDTH/2,FIELD_LENGTH,FIELD_WIDTH);
}

void BallGraphicsItem::setNewPosition(QVector2D p)
{
    QVector2D tmp(p.x(), -p.y());
    path.push_front(tmp);
    if(path.size() > 20) {
        path.pop_back();
    }
}

void BallGraphicsItem::clearPositions()
{
    this->path.clear();
}
