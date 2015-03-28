#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../server/definition/SSLBall.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ---------------------- plotter configuration ---------------------------
    ui->plot_1->addGraph(); // blue line
    ui->plot_1->graph(0)->setPen(QPen(Qt::blue));
    ui->plot_1->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui->plot_1->graph(0)->setAntialiasedFill(false);

    ui->plot_1->xAxis->setAutoTickStep(true);
    ui->plot_1->xAxis->setTickStep(2);
    ui->plot_1->axisRect()->setupFullAxesBox();
    ui->plot_1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->plot_1->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_1->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plot_1->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_1->yAxis2, SLOT(setRange(QCPRange)));


    // ----------------------- Scatter Configuration ---------------------------
    ui->plot_2->addGraph(); // blue line
    ui->plot_2->graph(0)->setPen(QPen(Qt::blue));
    ui->plot_2->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot_2->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlusCircle, 4));

    ui->plot_2->addGraph(); // blue line
    ui->plot_2->graph(1)->setPen(QPen(Qt::red));
    ui->plot_2->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->plot_2->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlusCircle, 6));

    ui->plot_2->addGraph(); // blue line
    ui->plot_2->graph(2)->setPen(QPen(Qt::green));
    ui->plot_2->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->plot_2->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 30));


    ui->plot_2->xAxis->setTickStep(2);
    ui->plot_2->axisRect()->setupFullAxesBox();
    ui->plot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot_2->xAxis->setRange(-10000, 10000);
    ui->plot_2->yAxis->setRange(-10000, 10000);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->plot_2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_2->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plot_2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_2->yAxis2, SLOT(setRange(QCPRange)));

    timer.setInterval(50);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerOVF()));
    timer.start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerOVF()
{
    static double start_time;

    VisionFilter::getInstance()->check();

//    double ball_err = SSLWorldModel::getInstance()->mainBall()->Speed().lenght();

    double ax_len = VisionFilter::getInstance()->ballFilter->m_acceleration.lenght();
    double ax_arc = VisionFilter::getInstance()->ballFilter->m_acceleration.arctan();

    double alfa = VisionFilter::getInstance()->ballFilter->alphaBetaFilter.m_alfa;
    double beta = VisionFilter::getInstance()->ballFilter->alphaBetaFilter.m_beta;

    Vector2D clusteredSpeed__ = VisionFilter::getInstance()->ballFilter->m_clusteredVelocity;
//    qDebug() << "Ball Raw Acceleration = " << data_1;
//             << "Ball Raw Displacement = " << ball_disp;

    QVector<double> values;
    values << clusteredSpeed__.X() << ax_len /1000000.0 << alfa;
//    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
//    if(VisionFilter::getInstance()->cameraLastFrameTime[0] == 0) {
//        start_time = key;
//    }
//    key -= start_time;

    double key = VisionFilter::getInstance()->cameraLastFrameTime[0];
    key-= ((int)key/1000) * 1000.0;

    ui->plot_1->graph(0)->addData(key, values[0]);
    ui->plot_1->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->plot_1->replot();

    if (key == 0)
        return;

    QVector<double> last_k_data_x;
    QVector<double> last_k_data_y;
    Vector2D speed = VisionFilter::getInstance()->ballFilter->m_rawVelocity;
    for(int i=0; i<4; i++) {
        if( i >= VisionFilter::getInstance()->ballFilter->rawData.size() )
            break;
        Vector2D speed_ = VisionFilter::getInstance()->ballFilter->getRawData(i).velocity;
        last_k_data_x.push_back(speed_.X());
        last_k_data_y.push_back(speed_.Y());
    }

    ui->plot_2->graph(0)->addData(speed.X(), speed.Y());
    ui->plot_2->graph(1)->setData(last_k_data_x, last_k_data_y);

    ui->plot_2->graph(2)->clearData();
    Vector2D filteredSpeed = VisionFilter::getInstance()->ballFilter->m_filteredVelocity;
    ui->plot_2->graph(2)->addData( filteredSpeed.X(), filteredSpeed.Y() );

    ui->plot_2->replot();
}

void MainWindow::on_actionPlayStop_toggled(bool arg1)
{
    if(arg1) {
        timer.start();
        VisionFilter::getInstance()->cameraLastFrameTime[0] = 0;
        VisionFilter::getInstance()->cameraLastFrameTime[1] = 0;

        ui->plot_2->graph(0)->clearData();
        ui->plot_2->graph(1)->clearData();
        ui->plot_2->graph(2)->clearData();
    }
    else
        timer.stop();
}
