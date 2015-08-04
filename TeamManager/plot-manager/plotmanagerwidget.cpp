#include "plotmanagerwidget.h"
#include "ui_plotmanagerwidget.h"
#include "plotwidget.h"
#include "QDateTime"
#include <sys/socket.h>
#include "../../server/paramater-manager/parametermanager.h"

PlotManagerWidget::PlotManagerWidget(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::PlotManagerWidget)
{
    mUi->setupUi(this);
    qRegisterMetaType<Plotter_Packet>("Plotter_Packet");

    char opt=1;
    setsockopt(mSocket.socketDescriptor(), SOL_RAW, SO_REUSEADDR, &opt, sizeof(int));
    connect(&mSocket, SIGNAL(readyRead()), this, SLOT(processPendingData()));


//    mPort = ParameterManager::getInstance()->get<int>("network.plotter_port");
    mPort = 4002;
    address = "127.0.0.1";
//    this->joinMulticastNetwork();

    // test
//    Plotter_Packet test_packet;
//    test_packet.set_name("test_1");
//    test_packet.add_values(20);
//    test_packet.add_legends("X");
//    this->newPlotMessage(test_packet);

//    test_packet.set_name("test_2");
//    test_packet.add_values(2000);
//    test_packet.add_legends("Y");
//    this->newPlotMessage(test_packet);
}

PlotManagerWidget::~PlotManagerWidget()
{
    delete mUi;
}

void PlotManagerWidget::newPlotMessage(Plotter_Packet packet)
{
//    mtx.lock();
    QString value_name = packet.name().c_str();
    const int values_size = packet.values_size();
    const int legends_size = packet.legends_size();
    packet.legends();
    if( !mPlotsMap.keys().contains(value_name) ) {
        PlotWidget* new_plot = 0;
        if( packet.values_size() > 0 )
            new_plot = new PlotWidget(packet.values_size(), this);
        if(new_plot) {
            new_plot->setName(value_name);

            if(packet.legends_size() == packet.values_size()) {
                QStringList legends;
                for(int i=0; i<packet.legends_size(); i++)
                    legends.append(QString(packet.legends(i).c_str()));
                new_plot->setLegends(legends);
            }
            mPlotsMap.insert(value_name, new_plot);
            mUi->scrollAreaLayout->addWidget(new_plot);
            connect(new_plot, SIGNAL(closeMe(QString)), this, SLOT(quitPlot(QString)));
        }
    }

    if( mPlotsMap.keys().contains(value_name) ) {
        double key;
        if(packet.has_key())
            key = packet.key();
        else
            key = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch()/1000.0;
        QVector<double> values;
        for(int i=0; i<packet.values_size(); i++)
            values.append( packet.values(i) );
        mPlotsMap[value_name]->addValue(key, values);
    }
//    mtx.unlock();
}

void PlotManagerWidget::joinMulticastNetwork()
{
#if QT_VERSION >= 0x050000
    if(mSocket.bind(QHostAddress::AnyIPv4, mPort, QUdpSocket::ShareAddress))
#else
    if(mSocket.bind(QHostAddress::Any, mPort, QUdpSocket::ShareAddress))
#endif
        qDebug() << "Binded Successfully" ;
    else {
        qDebug() << "Failed to Bind";
        QTimer::singleShot(3000, this, SLOT(joinMulticastNetwork(address)));
        return;
    }

    mSocket.joinMulticastGroup(QHostAddress(QHostAddress::Any));
}

void PlotManagerWidget::quitPlot(QString name)
{
    if(mPlotsMap.contains(name)) {
        PlotWidget* quitted_plot = mPlotsMap[name];
        mPlotsMap.remove(name);
        quitted_plot->deleteLater();
    }
}

void PlotManagerWidget::setPlotMinimized(QString name, bool minimized)
{
//    if(mPlotsMap.contains(name)) {
//        mPlotsMap[name]->resize();
//    }
//    if(minimized) {

//    }
}

void PlotManagerWidget::processPendingData()
{
    QByteArray receivedData;

    while (mSocket.hasPendingDatagrams())
    {
        receivedData.resize(mSocket.pendingDatagramSize());
        mSocket.readDatagram(receivedData.data(), receivedData.size());
    }

    qDebug() << "New plotter packet received. size # " << receivedData.size();

    Plotter_Packet packet;
    packet.ParseFromArray(receivedData.data(), receivedData.size());

    this->newPlotMessage(packet);
}

void PlotManagerWidget::plot(double value, QString plot_name, QString category)
{
    Plotter_Packet pp;
    pp.add_values(value);
    pp.add_legends(plot_name.toStdString().c_str());
    pp.set_name(category.toStdString().c_str());
    newPlotMessage(pp);
}
