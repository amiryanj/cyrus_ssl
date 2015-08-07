#ifndef _FIELDGRAPHICSVIEW_H
#define _FIELDGRAPHICSVIEW_H

#include <QGraphicsView>

class FieldGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit FieldGraphicsView(QGraphicsScene* scene = NULL, QWidget * parent=0);


private slots:
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QPointF mouseLastPosition;

};

#endif // _FIELDGRAPHICSVIEW_H
