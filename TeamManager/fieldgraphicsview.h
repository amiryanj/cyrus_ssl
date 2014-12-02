#ifndef _FIELDGRAPHICSVIEW_H
#define _FIELDGRAPHICSVIEW_H

#include <QGraphicsView>

class FieldGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit FieldGraphicsView(QGraphicsScene* scene = NULL, QWidget * parent=0);

    void wheelEvent(QWheelEvent *event);

signals:
    void mousewheel(float );

};

#endif // _FIELDGRAPHICSVIEW_H
