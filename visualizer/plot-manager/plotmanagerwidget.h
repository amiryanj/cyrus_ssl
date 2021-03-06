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
    void newPlotMessage(const Plotter_Packet& packet);

private slots:
    void processPendingData();
    void plot(double value, const std::string &plot_name, const std::string &category);
    void joinMulticastNetwork();

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
