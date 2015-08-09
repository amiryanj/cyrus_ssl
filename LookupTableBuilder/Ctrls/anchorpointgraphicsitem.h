#ifndef ANCHORPOINTGRAPHICSVIEW_H
#define ANCHORPOINTGRAPHICSVIEW_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QRectF>
#include <QBrush>
#include <QPen>
#include <QGraphicsSceneMouseEvent>

class AnchorPointGraphicsItem : public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit AnchorPointGraphicsItem(QGraphicsScene* scene, const QRectF& qRect, const QBrush& brush = QBrush(), const QPen& pen = QPen());
    
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsScene* mScene;
    bool m_pressed;

    void removeItem();

signals:
    void dragStart(AnchorPointGraphicsItem*);
    void dragEnd(AnchorPointGraphicsItem*);
    void onStateChanged(AnchorPointGraphicsItem*);
    void removedItem(AnchorPointGraphicsItem*);
    
public slots:
    
};

#endif // ANCHORPOINTGRAPHICSVIEW_H
