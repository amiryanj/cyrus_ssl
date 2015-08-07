#ifndef GRAPHPOINT_H
#define GRAPHPOINT_H

#import "Logic/graph.h"
#import <QGraphicsEllipseItem>

class GraphPoint : public Graph, public QGraphicsEllipseItem
{
public:
    GraphPoint();
};

#endif // GRAPHPOINT_H
