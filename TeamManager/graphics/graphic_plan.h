#ifndef GRAPHIC_PLAN_H
#define GRAPHIC_PLAN_H
#include <QGraphicsItem>
#include <QImage>
#include <QVector3D>

class PlanGraphicsItem : public QGraphicsItem
{

public:
    bool isInvisible;

    QImage image;
    PlanGraphicsItem(Qt::GlobalColor color);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    QPainterPath shape() const
    {
        QPainterPath p_path;
        p_path.addEllipse(boundingRect());
        return p_path;
    }

    void setPath(QVector<QVector3D> p);
    void clearPath();

private:
    Qt::GlobalColor myColor;
    int myRadius;
    QVector<QVector3D> path;
};

#endif // GRAPHIC_PLAN_H
