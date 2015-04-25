#ifndef _PLOTWIDGET_H
#define _PLOTWIDGET_H

#include <QTimer>
#include "qcustomplot.h"

namespace Ui {
class PlotWidget;
}

class PlotWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlotWidget(int graphsCount = 1, QWidget *parent = 0);

    void setName(QString name);
    void setLegends(QStringList legends);

    void addValue(double key, QVector<double> val);    
    void addValue(double key, double val);
    void addValue(QDateTime dateTime, double value);
    void addValue(double value);

    void setConnected(bool connected);

    void setYAxisRange(double lower, double upper);
    ~PlotWidget();

signals:
    void closeMe(QString);
    void setMeMinimized(QString, bool);
    
private:
    Ui::PlotWidget *ui;
    int graphsCount;
    double mKey;
    QString plotName;
    bool connected;

private slots:
//    void realtimeDataSlot();
    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void graphClicked(QCPAbstractPlottable *plottable);
    void on_closeButton_clicked();
    void on_minimizeButton_clicked(bool checked);
    void on_pauseButton_clicked(bool checked);
};

#endif // _PLOTWIDGET_H
