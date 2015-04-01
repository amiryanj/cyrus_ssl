#ifndef _SCATTERPLOTWIDGET_H
#define _SCATTERPLOTWIDGET_H

#include <QWidget>
#include "plot-manager/qcustomplot.h"

namespace Ui {
class ScatterPlotWidget;
}

class ScatterPlotWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ScatterPlotWidget(QWidget *parent = 0);
    ~ScatterPlotWidget();

    void setData(QVector<QPoint> a, QVector<QPoint> b);
    void clearData();
    
private:
    Ui::ScatterPlotWidget *ui;
};

#endif // SCATTERPLOTWIDGET_H
