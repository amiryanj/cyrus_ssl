#include "anchorpointgraphicsitem.h"

#include <QDebug>

AnchorPointGraphicsItem::AnchorPointGraphicsItem(QGraphicsScene* scene, const QRectF& qRect, const QBrush& brush, const QPen& pen) :
    QGraphicsEllipseItem(0),
    mScene(scene)
{
    mScene->addEllipse(qRect, pen, brush);
    this->setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);

}

void AnchorPointGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug()<<"pressed";
}

void AnchorPointGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

}

void AnchorPointGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::RightButton){

    }
}

void AnchorPointGraphicsItem::removeItem(){
    mScene->removeItem(this);
    emit removedItem(this);
    emit onStateChanged(this);
}
