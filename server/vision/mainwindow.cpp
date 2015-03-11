#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../definition/SSLBall.h"
#include "VisionFilter.h"
#include "BallFilter.h"

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

    double ball_err = SSLWorldModel::getInstance()->mainBall()->Acceleration().lenght();

    double ball_disp = VisionFilter::getInstance()->ballFilter->getFilteredSpeed().lenght();


    qDebug() << "Ball Raw Acceleration = " << ball_err
             << "Ball Raw Displacement = " << ball_disp;

    QVector<double> values;
    values << ball_err << ball_disp;
    pw_->addValue(counter/50.0, values);
}
