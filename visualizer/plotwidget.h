#ifndef _PLOTWIDGET_H
#define _PLOTWIDGET_H

#include <QTimer>
#include <qcustomplot.h>

namespace Ui {
class PlotWidget;
}

class PlotWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlotWidget(int numGraphs = 1, QWidget *parent = 0);

    void addValue(double key, QVector<double> val);    
    void addValue(double key, double val);
    void addValue(QDateTime dateTime, double value);
    void addValue(double value);
    ~PlotWidget();
    
private:
    Ui::PlotWidget *ui;
    int numGraphs;
    double mKey;

private slots:
//    void realtimeDataSlot();
    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void graphClicked(QCPAbstractPlottable *plottable);
};

#endif // _PLOTWIDGET_H
