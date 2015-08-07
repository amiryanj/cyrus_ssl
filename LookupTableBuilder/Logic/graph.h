#ifndef GRAPH_H
#define GRAPH_H

#include <QList>
#include <QVector2D>

class Graph
{
public:
    Graph();
    ~Graph();

    void addPoint(QVector2D& v);
    void addPoint(int x, int y);

    int getSize();
    void removeItem(int i);
    QVector2D& getPoint(int i);
    void sortItems();

    QVector2D getFunctionAtX(qreal x);
private:
    QList<QVector2D*> point_list;

};

#endif // GRAPH_H
