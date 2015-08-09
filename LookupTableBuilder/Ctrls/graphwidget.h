#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QString>
#include "Logic/graph.h"

namespace Ui {
    class GraphWidget;
}

class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = 0);
    ~GraphWidget();

    void setXLen(int len);
    void setYLen(int len);
    int addGraph();
    int getGraphCount();
    Graph getGraph(int);
    Graph getSelectedGraph();
    void setSelectedGraph(int);

protected:
    virtual void paintEvent(QPaintEvent *);
private:
    Ui::GraphWidget *ui;

    QList<Graph> graphList;
    int xLen;
    int yLen;

    int selectedGraphIndex;

};

#endif // GRAPHWIDGET_H
