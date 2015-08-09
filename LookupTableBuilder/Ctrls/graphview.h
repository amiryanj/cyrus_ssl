#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>
#include "clickablescene.h"
#include "Logic/graph.h"
#include <QList>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


class GraphView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphView(QWidget *parent = 0);
    ~GraphView();

    Graph *getGraph(int i);
    QList<Graph*> getGraphList();

    int getW();
    int getH();
    void setWH(int w, int h);

    void setSelectedGraph(int);
    void addGraph();
    void removeGraphs();

    void redraw();
private:
    static const int POINT_RADIUS = 10;

    QGraphicsScene* mScene;
    QList<Graph*>* mGraphList;

    int selectedGraph;
    int clickedGraphPoint;

    qreal w;
    qreal h;

    const QBrush getColor(int i);

private slots:
    void wheelEvent(QWheelEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mousePressEvent(QMouseEvent *e);
//    void mouseReleaseEvent(QMouseEvent *event);

    void onMousePressEvent(QGraphicsSceneMouseEvent *event);
    void onMouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void onMouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // GRAPHVIEW_H
