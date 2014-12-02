#include "fieldgraphicsview.h"
#include <QMouseEvent>

FieldGraphicsView::FieldGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene ,parent)
{
    setMouseTracking(true);
    setCursor(Qt::OpenHandCursor);
    setRenderHint(QPainter::Antialiasing);
}

void FieldGraphicsView::wheelEvent(QWheelEvent *event)
{
    static float numDegrees = 10;
    if(event->delta() > 0)
        numDegrees ++;
    else
        numDegrees --;

//    qDebug()<<numDegrees;
    QTransform t;
    t.scale(numDegrees/1000.0, numDegrees/1000.0);
    this->setTransform(t);
//    this->scale(numDegrees/10.0, numDegrees/10.0);
    emit mousewheel(numDegrees);

}
