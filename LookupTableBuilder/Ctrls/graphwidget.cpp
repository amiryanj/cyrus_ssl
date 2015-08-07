#include "graphwidget.h"
#include "ui_graphwidget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>

GraphWidget::GraphWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::GraphWidget),
        xLen(1000),
        yLen(255)
{
    ui->setupUi(this);

    this->selectedGraphIndex = 0;
}

void GraphWidget::paintEvent(QPaintEvent * paint){
    Q_UNUSED(paint);
    QPainter* qp = new QPainter(this);

    qp->fillRect(QRectF(0, 0, this->width(), this->height()), QColor::fromRgb(255, 255, 255));


    //qp->setBrush(Qt::CrossPattern);
    //qp->drawRect(0, 0, this->width(), this->height());

    QPen pen(Qt::black, 2, Qt::SolidLine);
    qp->setPen(pen);
    qp->drawLine(0, 0, 0, this->height());
    qp->drawLine(0, this->height()/2, this->width(), this->height()/2);



    delete qp;
}

void GraphWidget::setXLen(int len){
    this->xLen = len;
}

void GraphWidget::setYLen(int len){
    this->xLen = len;
}

int GraphWidget::addGraph(){
    Graph g;
    graphList.append(g);
    return graphList.length();
}

int GraphWidget::getGraphCount(){
    return graphList.length();
}

Graph GraphWidget::getGraph(int index){
    return graphList.at(index);
}

Graph GraphWidget::getSelectedGraph(){
    return graphList.at(selectedGraphIndex);
}

void GraphWidget::setSelectedGraph(int i){
    selectedGraphIndex = i;
}

GraphWidget::~GraphWidget()
{
    delete ui;
}
