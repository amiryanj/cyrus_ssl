#ifndef _PLOTMANAGERWIDGET_H
#define _PLOTMANAGERWIDGET_H

#include <QWidget>
#include <QMap>
#include <QUdpSocket>
#include "../common/protoc/plotter/cpp/message_plotter.pb.h"

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

private slots:
    void processPendingData();
    void newPlotMessage(const Plotter_Packet& packet);
    void joinMulticastNetwork();

    void quitPlot(QString name);
    void setPlotMinimized(QString name, bool minimized);
    
private:
    Ui::PlotManagerWidget *mUi;
    QMap<QString , PlotWidget*> mPlotsMap;

    QUdpSocket mSocket;
    int mPort;
};

#endif // PLOTMANAGERWIDGET_H
