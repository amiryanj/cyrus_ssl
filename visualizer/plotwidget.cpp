#include "plotwidget.h"
#include "ui_plotwidget.h"

PlotWidget::PlotWidget(int numGraphs, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotWidget)
{
    ui->setupUi(this);

    // Add Drag, Zoom and ... capabilities
    ui->myPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                QCP::iSelectLegend | QCP::iSelectPlottables);

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->myPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->myPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->myPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->myPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->myPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->myPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->myPlot->yAxis2, SLOT(setRange(QCPRange)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(ui->myPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
//    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));

    // ************************************************
    // ************** Set a new title *****************
    // ************************************************
//    ui->myPlot->plotLayout()->insertRow(0);     // Adding a row to insterting new Title
//    ui->myPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->myPlot, "Robot States"));

    // ************************************************
    // ************* Set Axis Settings ****************
    // ************************************************
//    ui->myPlot->xAxis->setTickLabelType(QCPAxis::ltNumber);
    ui->myPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->myPlot->xAxis->setDateTimeFormat("mm:ss");
    ui->myPlot->xAxis->setAutoTickStep(false);
    ui->myPlot->xAxis->setTickStep(1);
    ui->myPlot->xAxis->setTickLabelRotation(30);

    ui->myPlot->yAxis->setRange(100, 50000);
//    ui->myPlot->yAxis->setLabel("Velo (mm/s)");

//    ui->myPlot->axisRect()->setupFullAxesBox();


    // ************************************************
    // ************* Adding New Graph *****************
    // ************************************************
    this->numGraphs = numGraphs;
    for(int i=0; i< numGraphs; i++) {
        ui->myPlot->addGraph(/*ui->myPlot->xAxis,ui->myPlot->yAxis*/);
        if(i==0) {
            ui->myPlot->graph(2*i)->setPen(QPen(Qt::red));
            ui->myPlot->graph(2*i)->setName(QString("Actual Vel"));
        }
        else if(i==1) {
            ui->myPlot->graph(2*i)->setPen(QPen(Qt::green));
            ui->myPlot->graph(2*i)->setName(QString("Desired Vel"));
        }
        else {
            ui->myPlot->graph(2*i)->setPen(QPen(Qt::yellow));
            ui->myPlot->graph(2*i)->setName(QString("Applied Vel%1"));
        }
        // Add a blue dot in end of graph
        ui->myPlot->addGraph();
        ui->myPlot->graph(2*i+1)->setPen(QPen(Qt::blue));
        ui->myPlot->graph(2*i+1)->setLineStyle(QCPGraph::lsNone);
        ui->myPlot->graph(2*i+1)->setScatterStyle(QCPScatterStyle::ssDisc);
    }
}

void PlotWidget::addValue(double key, QVector<double> val)
{
    for(int i=0; i<(qMin(numGraphs, val.size())); i++) {
          // add data to lines:
          ui->myPlot->graph(2*i)->addData(key, val[i]);
          ui->myPlot->graph(2*i)->removeDataBefore(key-30);
          ui->myPlot->graph(2*i+1)->clearData();
          ui->myPlot->graph(2*i+1)->addData(key, val[i]);
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->myPlot->xAxis->setRange(key+2, 20, Qt::AlignRight);
    ui->myPlot->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      //ui->statusBar->showMessage(QString("%1 FPS, Total Data points: %2")
        //.arg(frameCount/(key-lastFpsKey), 0, 'f', 0).arg(ui->myPlot->graph(0)->data()->count()+ui->myPlot->graph(2)->data()->count()), 0);
      lastFpsKey = key;
      frameCount = 0;
    }
}

void PlotWidget::addValue(double key, double val)
{
    QVector<double> valVector;
    valVector << val;
    addValue(key, valVector);
}

void PlotWidget::addValue(QDateTime dateTime, double value)
{
    mKey = dateTime.toMSecsSinceEpoch()/1000.0;

    addValue(mKey, value);
}

void PlotWidget::addValue(double value)
{
    mKey = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0 ;
    static int counter = 0;
    counter++;

    addValue(counter/10.0, value);
}

PlotWidget::~PlotWidget()
{
    delete ui;
}

void PlotWidget::selectionChanged()
{
   /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
   */

    // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->myPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->myPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            ui->myPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->myPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->myPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->myPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->myPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->myPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            ui->myPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->myPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->myPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->myPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // synchronize selection of graphs with selection of corresponding legend items:
    for (int i=0; i<ui->myPlot->graphCount(); ++i)
    {
        QCPGraph *graph = ui->myPlot->graph(i);
        QCPPlottableLegendItem *item = ui->myPlot->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected())
        {
            item->setSelected(true);
            graph->setSelected(true);
        }
    }
}

void PlotWidget::mousePress()
{
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged

    if (ui->myPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->myPlot->axisRect()->setRangeDrag(ui->myPlot->xAxis->orientation());
    else if (ui->myPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->myPlot->axisRect()->setRangeDrag(ui->myPlot->yAxis->orientation());
    else
        ui->myPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void PlotWidget::mouseWheel()
{
    // if an axis is selected, only allow the direction of that axis to be zoomed
    // if no axis is selected, both directions may be zoomed

    if (ui->myPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->myPlot->axisRect()->setRangeZoom(ui->myPlot->xAxis->orientation());
    else if (ui->myPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->myPlot->axisRect()->setRangeZoom(ui->myPlot->yAxis->orientation());
    else
        ui->myPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void PlotWidget::graphClicked(QCPAbstractPlottable *plottable)
{
//    ui->vel_label->setText(plottable->name());
}

