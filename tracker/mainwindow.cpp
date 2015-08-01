#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../server/definition/SSLBall.h"
#include "../shared/utility/generalmath.h"

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


    ui->tabWidget->hide();

    PMW = new PlotManagerWidget(this);
    ui->verticalLayout_pmw->addWidget(PMW);


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
    VisionFilter::getInstance()->check();

    Vector3D filtered_vel = VisionFilter::getInstance()->getUnderTestRobotFilteredVelocity();
    Vector3D filtered_pos = VisionFilter::getInstance()->getUnderTestRobotFilteredPosition();

    cout << "MainWindow: filtered_vel: " ;
    filtered_vel.print(cout);

    Vector3D raw_vel = VisionFilter::getInstance()->getUnderTestRobotRawVelocity();
    Vector3D raw_pos = VisionFilter::getInstance()->getUnderTestRobotRawPosition();

    cout << "MainWindow: raw_vel: " ;
    raw_vel.print(cout);
    cout << endl;

    Plotter_Packet pp;
    pp.set_name("Vel");

    pp.add_values(filtered_vel.Y());
    pp.add_legends("filtered");

    pp.add_values(raw_vel.Y());
    pp.add_legends("raw");
    PMW->newPlotMessage(pp);


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
