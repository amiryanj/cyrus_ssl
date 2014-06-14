#ifndef GRAPHIC_INTERSECT_H
#define GRAPHIC_INTERSECT_H

#include <QGraphicsItem>
#include <vector2d.h>
#include "Concepts.h"
#include "general.h"

class IntersectGraphicsItem : public QGraphicsItem
{
public:
   bool isInvisible;

    IntersectGraphicsItem();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void setRobotPosition(double x , double y);

    QPainterPath shape() const
    {
        QPainterPath path;
        path.addEllipse(boundingRect());
        return path;
    }

private:
    Vector2D robotPosition;

};

#endif // GRAPHIC_INTERSECT_H
