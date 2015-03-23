#include "fieldview.h"
#include <QScrollBar>
#include <QDebug>

FieldView::FieldView(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setInteractive(true);
    this->setDragMode(ScrollHandDrag);
    mTransform = this->transform();
}

void FieldView::wheelEvent(QWheelEvent *event)
{
    mTransform = this->transform();
    if(event->delta()> 0)
        mTransform.scale(1.25, 1.25);
    else
        mTransform.scale(0.8, 0.8);

    this->setTransform(mTransform);
}

void FieldView::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
        mTransform = this->transform();
        QPointF translation = event->posF() - mouseLastPosition;
//        mTransform.translate( translation.x()*2000, translation.y()*2000 );
//        this->setTransform(mTransform);
        mouseLastPosition = event->posF();
        QScrollBar *h_scroll_bar = this->horizontalScrollBar();
        h_scroll_bar->setValue(h_scroll_bar->value() - translation.x());
        QScrollBar *v_scroll_bar = this->verticalScrollBar();
        v_scroll_bar->setValue(v_scroll_bar->value() - translation.y());
    }
}

void FieldView::mousePressEvent(QMouseEvent *event)
{
//    event->ignore();
    mouseLastPosition = event->posF();
}


