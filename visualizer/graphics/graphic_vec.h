#ifndef GRAPHIC_VEC_H
#define GRAPHIC_VEC_H
#include <QGraphicsItem>
#include <QImage>
#include "Concepts.h"
#include "general.h"

class VectorGraphicsItem : public QGraphicsItem
{

public:
    VectorGraphicsItem(Qt::GlobalColor color = Qt::cyan);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    QPainterPath shape() const
    {
        QPainterPath path;
        path.addEllipse(boundingRect());
        return path;
    }
    void setEnd(double x, double y);
    void setGlobalOrien(bool g);

private:    
    bool globalOrien;
    QPointF end;    
    Qt::GlobalColor color;
};

#endif // GRAPHIC_VEC_H
