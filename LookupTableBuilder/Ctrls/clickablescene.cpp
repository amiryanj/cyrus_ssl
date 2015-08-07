#include "clickablescene.h"
#include <QGraphicsScene>
#include <QDebug>

ClickableScene::ClickableScene(const QRect& r) : QGraphicsScene(r)
{

}

void ClickableScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit onMousePressEvent(event);
}

void ClickableScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    emit onMouseMoveEvent(event);
}

void ClickableScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    emit onMouseReleaseEvent(event);
}
