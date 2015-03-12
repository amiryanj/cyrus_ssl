#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../definition/SSLBall.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pw_ = new PlotWidget(2, this);
    ui->verticalLayout->addWidget(pw_);

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
    static int counter = 0;
    counter ++;

//    double ball_err = SSLWorldModel::getInstance()->mainBall()->Speed().lenght();

    double data_1 = VisionFilter::getInstance()->ballFilter->getUnfilteredSpeed().lenght();
    double data_2 = VisionFilter::getInstance()->ballFilter->getFilteredSpeed().lenght();

    double alfa = VisionFilter::getInstance()->ballFilter->naiveFilter.m_alfa;

//    qDebug() << "Ball Raw Acceleration = " << data_1;
//             << "Ball Raw Displacement = " << ball_disp;

    QVector<double> values;
    values << data_1 << data_2;
    pw_->addValue( counter /10.0, values );
}
