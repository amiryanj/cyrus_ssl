#ifndef GRAPHIC_BALL_H
#define GRAPHIC_BALL_H
#include <QGraphicsItem>
#include <QImage>
#include <QVector3D>
#include <QVector2D>
#include <QQueue>
#include <QVector>

class BallGraphicsItem : public QGraphicsItem
{

public:
    bool isInvisible;

    QImage image;
    BallGraphicsItem(Qt::GlobalColor color);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    QPainterPath shape() const
    {
        QPainterPath p_path;
        p_path.addEllipse(boundingRect());
        return p_path;
    }

    void setNewPosition(QVector2D p);
    void clearPositions();

private:
    Qt::GlobalColor myColor;
    int myRadius;
    QQueue<QVector2D> path;
};

#endif // GRAPHIC_BALL_H
