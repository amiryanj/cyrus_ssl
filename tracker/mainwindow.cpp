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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerOVF()
{
    static int counter = 0;
    counter ++;

//    double ball_err = SSLWorldModel::getInstance()->mainBall()->Speed().lenght();

    double data_0 = VisionFilter::getInstance()->ballFilter->getRawData(0).displacement.X();
    double data_1 = VisionFilter::getInstance()->ballFilter->getRawData(0).displacement.Y();
    double data_2 = VisionFilter::getInstance()->ballFilter->getRawData(2).displacement.X();

    double alfa = VisionFilter::getInstance()->ballFilter->naiveFilter.m_alfa;

//    qDebug() << "Ball Raw Acceleration = " << data_1;
//             << "Ball Raw Displacement = " << ball_disp;

    QVector<double> values;
//    if(data_1 != 0.0)
    values << data_0 << data_1 ;
    pw_->addValue( counter /10.0, values );
}

void MainWindow::on_actionPlayStop_toggled(bool arg1)
{
    if(arg1)
        timer.start();
    else
        timer.stop();
}
