#include "scatterplotwidget.h"
#include "ui_scatterplotwidget.h"

ScatterPlotWidget::ScatterPlotWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScatterPlotWidget)
{
    ui->setupUi(this);

    // ----------------------- Scatter Configuration ---------------------------
    ui->scatter->addGraph(); // blue circle
    ui->scatter->graph(0)->setPen(QPen(Qt::blue));
    ui->scatter->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->scatter->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlusCircle, 4));

    ui->scatter->addGraph(); // blue line
    ui->scatter->graph(1)->setPen(QPen(Qt::red));
    ui->scatter->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->scatter->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlusCircle, 5));

    ui->scatter->addGraph(); // blue line
    ui->scatter->graph(2)->setPen(QPen(Qt::green));
    ui->scatter->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->scatter->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 30));


    ui->scatter->xAxis->setTickStep(2);
    ui->scatter->axisRect()->setupFullAxesBox();
    ui->scatter->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->scatter->xAxis->setRange(-10000, 10000);
    ui->scatter->yAxis->setRange(-10000, 10000);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->scatter->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->scatter->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->scatter->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->scatter->yAxis2, SLOT(setRange(QCPRange)));
}

ScatterPlotWidget::~ScatterPlotWidget()
{
    delete ui;
}

void ScatterPlotWidget::setData(QVector<QPoint> a, QVector<QPoint> b)
{
    QVector<double> x;
    QVector<double> y;
    foreach (QPoint point, a) {
        x.append(point.x());
        y.append(point.y());
    }
    ui->scatter->graph(0)->setData(x, y);

    x.clear();
    y.clear();
    foreach (QPoint point, b) {
        x.append(point.x());
        y.append(point.y());
    }
    ui->scatter->graph(1)->setData(x, y);
    ui->scatter->replot();
}

void ScatterPlotWidget::clearData()
{
    ui->scatter->graph(0)->clearData();
    ui->scatter->graph(1)->clearData();
}



