#include "graph.h"

Graph::Graph()
{
}

Graph::~Graph()
{
    for(int i =0; i<point_list.length(); i++){
        delete point_list.at(i);
    }
}

void Graph::addPoint(QVector2D& v){
    QVector2D* g = new QVector2D(v);
    point_list.append(g);
}

void Graph::addPoint(int x, int y){
    QVector2D* v = new QVector2D(x, y);
    for(int i = 0; i< point_list.length(); i++){
        if(point_list.at(i)->x() == x){
            point_list.replace(i , v);
            return;
        } else if(point_list.at(i)->x() > x) {
            point_list.insert(i, v);
            return;
        }
    }
    point_list.append(v);
}

int Graph::getSize(){
    return point_list.length();
}

void Graph::removeItem(int i){
    point_list.removeAt(i);
}

QVector2D& Graph::getPoint(int i){
    return *point_list.at(i);
}

void Graph::sortItems() {
    for(int i = 0; i< point_list.length(); i++)
    {
        for(int j = i+1; j<point_list.length(); j++)
        {
            if(point_list.at(i)->x() > point_list.at(j)->x())
            {
                point_list.swap(i, j);
            }
        }
    }
}

QVector2D Graph::getFunctionAtX(qreal x)
{
    QVector2D result(0., 0.);
    if(point_list.size() < 2)
        return result;
    int begin_index = 0;
    int end_index;
    for(int i=1; i< point_list.size(); i++) {
        if( x < point_list.at(i)->x()) {
            end_index = i;
            break;
        }
        begin_index = i;
    }

    QVector2D diff = *(point_list.at(end_index)) - *(point_list.at(begin_index));
    qreal diff_x = x - point_list.at(begin_index)->x();
    qreal alfa = diff_x/diff.x();

    result = *(point_list.at(begin_index)) * (1-alfa) + *(point_list.at(end_index)) * alfa;
    result.setX(x);
    return result;
}
