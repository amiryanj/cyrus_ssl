#ifndef CLICKABLESCENE_H
#define CLICKABLESCENE_H

#include <QGraphicsScene>
#include <QRect>

class ClickableScene : public QGraphicsScene
{
     Q_OBJECT
public:
    ClickableScene(const QRect&);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals :
    void onMousePressEvent(QGraphicsSceneMouseEvent *event);
    void onMouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void onMouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CLICKABLESCENE_H
