#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QTimer>
#include "qcustomplot.h"

namespace Ui {
class PlotWidget;
}

class PlotWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlotWidget(int numGraphs = 1, QWidget *parent = 0);

    void addValue(double key, QVector<double> val);    
    ~PlotWidget();
    
private:
    Ui::PlotWidget *ui;
    int numGraphs;

private slots:
//    void realtimeDataSlot();
    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void graphClicked(QCPAbstractPlottable *plottable);
};

#endif // PLOTWIDGET_H
