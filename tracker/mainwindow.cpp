#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../server/definition/SSLBall.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pw_ = new PlotWidget(3, this);
    ui->verticalLayout->addWidget(pw_);

    timer.setInterval(10);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerOVF()));
    timer.start();

    pw_->setYAxisRange(-10, 10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerOVF()
{
    static int counter = 0;
    counter ++;

    VisionFilter::getInstance()->check();

//    double ball_err = SSLWorldModel::getInstance()->mainBall()->Speed().lenght();

    double ax_len = VisionFilter::getInstance()->ballFilter->m_acceleration.lenght();
    double ax_arc = VisionFilter::getInstance()->ballFilter->m_acceleration.arctan();

    double alfa = VisionFilter::getInstance()->ballFilter->naiveFilter.m_alfa;
    double beta = VisionFilter::getInstance()->ballFilter->naiveFilter.m_beta;

//    qDebug() << "Ball Raw Acceleration = " << data_1;
//             << "Ball Raw Displacement = " << ball_disp;

    QVector<double> values;
//    if(data_1 != 0.0)
    values << ax_len /1000000.0 << alfa;
    pw_->addValue( counter /30.0, values );
}

void MainWindow::on_actionPlayStop_toggled(bool arg1)
{
    if(arg1)
        timer.start();
    else
        timer.stop();
}
