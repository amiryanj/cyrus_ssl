#ifndef _PLOTMANAGERWIDGET_H
#define _PLOTMANAGERWIDGET_H

#include <QWidget>
#include <QMap>
#include <QMutex>
#include <QUdpSocket>
#include "../shared/proto/plotter/cpp/message_plotter.pb.h"

namespace Ui {
class PlotManagerWidget;
}

class PlotWidget;

class PlotManagerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlotManagerWidget(QWidget *parent = 0);
    ~PlotManagerWidget();

public slots:
    void plot(double value, QString plot_name, QString category);
    void newPlotMessage(Plotter_Packet packet);
    void joinMulticastNetwork();

private slots:
    void processPendingData();

    void quitPlot(QString name);
    void setPlotMinimized(QString name, bool minimized);
    
private:
    Ui::PlotManagerWidget *mUi;
    QMap<QString , PlotWidget*> mPlotsMap;

    QUdpSocket mSocket;
    QMutex mtx;
    int mPort;
    std::string address;
};

#endif // PLOTMANAGERWIDGET_H
