#ifndef GRAPHIC_CIRCEL_H
#define GRAPHIC_CIRCEL_H
#include <QGraphicsItem>
#include <QImage>
#include "Concepts.h"
#include "general.h"

class CircleGraphicsItem : public QGraphicsItem
{

public:
   bool isInvisible;

    CircleGraphicsItem(int radius, QColor color, int id= 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    QPainterPath shape() const
    {
        QPainterPath path;
        path.addEllipse(boundingRect());
        return path;
    }

private:
    QColor myColor;
    int  myID;
    int myRadius;
};

#endif // GRAPHIC_CIRCEL_H
