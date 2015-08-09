#include "fieldgraphicsview.h"
#include <QMouseEvent>
#include <QScrollBar>

FieldGraphicsView::FieldGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene ,parent)
{
    setMouseTracking(true);
    setCursor(Qt::OpenHandCursor);
    setRenderHint(QPainter::Antialiasing);

    QTransform t;
    t.scale(0.14, 0.14);
    setTransform(t);
}

void FieldGraphicsView::wheelEvent(QWheelEvent *event)
{    
    if(event->delta() > 0) {
        setTransform(this->transform().scale(1.2, 1.2));
    }
    else {
        setTransform(this->transform().scale(1./1.2, 1./1.2));
    }
}

void FieldGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
#if QT_VERSION >= 0x050000
        QPointF translation = event->localPos() - mouseLastPosition;
        mouseLastPosition = event->localPos();
#else
        QPointF translation = event->posF() - mouseLastPosition;
        mouseLastPosition = event->posF();
#endif
        QScrollBar *h_scroll_bar = this->horizontalScrollBar();
        h_scroll_bar->setValue(h_scroll_bar->value() - translation.x());
        QScrollBar *v_scroll_bar = this->verticalScrollBar();
        v_scroll_bar->setValue(v_scroll_bar->value() - translation.y());
    }
}

void FieldGraphicsView::mousePressEvent(QMouseEvent *event)
{
#if QT_VERSION >= 0x050000
    mouseLastPosition = event->localPos();
#else
    mouseLastPosition = event->posF();
#endif
}
