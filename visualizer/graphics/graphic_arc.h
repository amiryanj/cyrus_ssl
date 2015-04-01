#ifndef _GRAPHIC_ARC_H
#define _GRAPHIC_ARC_H
#include <QGraphicsItem>
#include <QImage>
#include "Concepts.h"
#include "general.h"

class ArcGraphicsItem : public QGraphicsItem
{

public:
    ArcGraphicsItem(QColor color = Qt::cyan);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    QPainterPath shape() const
    {
        QPainterPath path;
        path.addEllipse(boundingRect());
        return path;
    }
    void setArcLenght(float x);

private:    
    float arcLenght;
    QColor color;
};

#endif // GRAPHIC_VEC_H
