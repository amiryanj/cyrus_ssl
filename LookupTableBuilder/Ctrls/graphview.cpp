#include "graphview.h"

#include <QGraphicsRectItem>
#include <QVector2D>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

GraphView::GraphView(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setMouseTracking(true);

    mGraphList = new QList<Graph*>();
    selectedGraph = 0;
    clickedGraphPoint = -1;

    mScene = NULL;
    setWH(w, h);
}

GraphView::~GraphView(){
    if(mScene!=NULL)delete mScene;

    if(mGraphList!=NULL){
        for(int i =0 ; i<mGraphList->count(); i++){
            delete mGraphList->at(i);
        }
        delete mGraphList;
    }
}

void GraphView::redraw(){
    mScene->clear();
    QPen p(Qt::black, 3);

    mScene->setSceneRect(0, -h/2, w, h);

    mScene->addRect(0, -h/2, w, h, p, Qt::white);
    mScene->addLine(0, 0, mScene->width(), 0, p);

    for(int i =-5; i<=5; i++){
        mScene->addLine(0, h/10. *i, w, h/10. *i, QPen(Qt::red));
    }
    for(int i =0; i<20; i++){
        mScene->addLine((w/20)*i, -h/2, (w)/20*i, h/2, QPen(Qt::cyan));
    }

    for(int i = 0; i< mGraphList->count(); i++){
        //mGraphList->at(i)->sortItems();
        for(int j = 0; j<mGraphList->at(i)->getSize(); j++) {
            QVector2D point_j = mGraphList->at(i)->getPoint(j);
            mScene->addEllipse(point_j.x() - POINT_RADIUS/2,
                               -point_j.y() - POINT_RADIUS/2,
                               POINT_RADIUS, POINT_RADIUS, QPen(), getColor(i));
            if(j != 0){
                QVector2D point_j_1 = mGraphList->at(i)->getPoint(j-1);
                mScene->addLine(point_j_1.x(),
                                -point_j_1.y(),
                                point_j.x(),
                                -point_j.y(), QPen());
            }
        }
    }
}

Graph* GraphView::addGraph() {
    Graph* g = new Graph();
    g->addPoint(0, 0);
    g->addPoint(mScene->width(), 0);
    mGraphList->append(g);
    this->redraw();
    return g;
}

void GraphView::removeGraphs()
{
    if(mGraphList!=NULL){
        for(int i =0 ; i<mGraphList->count(); i++){
            delete mGraphList->at(i);
        }
    }
    mGraphList->clear();
    redraw();
}

const QBrush GraphView::getColor(int i){
    switch(i){
    case 0:
        return Qt::red;
        break;
    case 1:
        return Qt::blue;
        break;
    case 2:
        return Qt::green;
        break;
    case 3:
        return Qt::yellow;
        break;
    case 4:
        return Qt::cyan;
        break;
    case 5:
        return Qt::gray;
        break;
    }
}

void GraphView::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0) {
        setTransform(this->transform().scale(1.2, 1.2));
    }
    else {
        setTransform(this->transform().scale(1./1.2, 1./1.2));
    }
}

int GraphView::getW(){
    return w;
}

int GraphView::getH(){
    return h;
}

void GraphView::setWH(int w, int h){
    w*= 1.1;
    h*= 1.1;

    this->w = w;
    this->h = h;

    QRect r(0, -h/2, w, h);
    setWH(r);
}

void GraphView::setWH(QRect &r)
{
    this->w = r.width();
    this->h = r.height();

    if(mScene)
        delete mScene;

    mScene = new ClickableScene(r);

    this->setScene(mScene);
    mScene->setBackgroundBrush(Qt::gray);

    connect(mScene, SIGNAL(onMousePressEvent(QGraphicsSceneMouseEvent*)), this, SLOT(onMousePressEvent(QGraphicsSceneMouseEvent*)));
    connect(mScene, SIGNAL(onMouseMoveEvent(QGraphicsSceneMouseEvent*)), this, SLOT(onMouseMoveEvent(QGraphicsSceneMouseEvent*)));
    connect(mScene, SIGNAL(onMouseReleaseEvent(QGraphicsSceneMouseEvent*)), this, SLOT(onMouseReleaseEvent(QGraphicsSceneMouseEvent*)));

    for(int i = 0; i<mGraphList->count(); i++){
//        mGraphList->at(i)->getPoint(0).setX(0);
//        mGraphList->at(i)->getPoint(mGraphList->at(i)->getSize()-1).setX(mScene->width());
    }

    redraw();
}

Graph* GraphView::getGraph(int i){
    return mGraphList->at(i);
}

QList<Graph*> GraphView::getGraphList(){
    return *mGraphList;
}

void GraphView::onMousePressEvent(QGraphicsSceneMouseEvent *event){

    bool dblClick = (event->button() == Qt::RightButton);

    Graph* g = mGraphList->at(selectedGraph);
    for(int i = 0; i<g->getSize(); i++){

        if((abs(event->scenePos().x() - ((int)g->getPoint(i).x())) < POINT_RADIUS/2) &&
                (abs(event->scenePos().y() - (-(int)g->getPoint(i).y())) < POINT_RADIUS/2)){

            if(dblClick){
                if((i != 0) && (i != g->getSize()-1)){
                    g->removeItem(i);
                }
            }else{
                clickedGraphPoint = i;
            }

            redraw();
            return;
        }
    }

    if(dblClick){
        g->addPoint(event->scenePos().x(), -event->scenePos().y());
    }

    clickedGraphPoint = -1;
    redraw();
}

void GraphView::onMouseMoveEvent(QGraphicsSceneMouseEvent *event){

    if(clickedGraphPoint == -1) {
        Graph* g = mGraphList->at(selectedGraph);
        for(int i = 0; i<g->getSize(); i++){

            if((abs(event->scenePos().x() - ((int)g->getPoint(i).x())) < POINT_RADIUS/2) &&
                    (abs(event->scenePos().y() - (-(int)g->getPoint(i).y())) < POINT_RADIUS/2)){
                this->setCursor(Qt::PointingHandCursor);
                return;
            }
        }
        this->setCursor(Qt::ArrowCursor);
    } else {

        mGraphList->at(selectedGraph)->getPoint(clickedGraphPoint).setX(event->scenePos().x());
        if(clickedGraphPoint != 0){
            if(event->scenePos().x() <= mGraphList->at(selectedGraph)->getPoint(clickedGraphPoint-1).x())
                mGraphList->at(selectedGraph)->getPoint(clickedGraphPoint).setX(mGraphList->at(selectedGraph)->getPoint(clickedGraphPoint-1).x()+1);
        }else{
            mGraphList->at(selectedGraph)->getPoint(clickedGraphPoint).setX(0);
        }
        if(clickedGraphPoint != mGraphList->at(selectedGraph)->getSize()-1){
            if(event->scenePos().x() >= mGraphList->at(selectedGraph)->getPoint(clickedGraphPoint+1).x())
                mGraphList->at(selectedGraph)->getPoint(clickedGraphPoint).setX(mGraphList->at(selectedGraph)->getPoint(clickedGraphPoint+1).x()-1);
        }else{
            mGraphList->at(selectedGraph)->getPoint(clickedGraphPoint).setX(mScene->width());
        }


        qreal y_ = qMax(-qMin(event->scenePos().y(), h/2), -h/2);
        mGraphList->at(selectedGraph)->getPoint(clickedGraphPoint).setY(y_);
        redraw();
    }
}

void GraphView::onMouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(clickedGraphPoint == -1) return;
    clickedGraphPoint = -1;
}

void GraphView::setSelectedGraph(int i){
    this->selectedGraph = i;
}
