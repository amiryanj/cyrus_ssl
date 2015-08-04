#include "plotwidget.h"
#include "ui_plotwidget.h"

PlotWidget::PlotWidget(int numGraphs, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotWidget)
{
    ui->setupUi(this);

    // Add Drag, Zoom and ... capabilities
    ui->myPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectItems);

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->myPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->myPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->myPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->myPlot->yAxis2, SLOT(setRange(QCPRange)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(ui->myPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));

    // ************* Set Axis Settings ****************
    ui->myPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->myPlot->xAxis->setDateTimeFormat("mm:ss");
    ui->myPlot->xAxis->setAutoTickStep(true);
    ui->myPlot->xAxis->setTickStep(1);
    ui->myPlot->xAxis->setTickLabelRotation(30);

    ui->myPlot->yAxis->setRange(-1, 1);

    // ************* Adding New Graph *****************
    QVector<QColor> colorList;
    colorList << Qt::green << Qt::yellow << Qt::red << Qt::darkGreen << Qt::darkYellow << Qt::darkRed;
    this->graphsCount = numGraphs;
    for(int i=0; i< numGraphs; i++) {
        ui->myPlot->addGraph(/*ui->myPlot->xAxis,ui->myPlot->yAxis*/);
        ui->myPlot->graph(2*i)->setPen(colorList[i%numGraphs]);

        // Add a blue dot in end of graph
        ui->myPlot->addGraph();
        ui->myPlot->legend->removeItem(ui->myPlot->legend->itemCount()-1); // don't show two graphs in legend
        ui->myPlot->graph(2*i+1)->setPen(QPen(Qt::blue));
        ui->myPlot->graph(2*i+1)->setLineStyle(QCPGraph::lsNone);
        ui->myPlot->graph(2*i+1)->setScatterStyle(QCPScatterStyle::ssDisc);
    }
    connected = true;
    freezed = false;
}

void PlotWidget::setName(QString name)
{
    this->plotName = name;
    ui->minimizeButton->setToolTip("Plot: " + name);
}

void PlotWidget::setLegends(QStringList legends)
{
    ui->myPlot->legend->setVisible(true);
    ui->myPlot->legend->setFont(QFont("Ubuntu", 9));
    ui->myPlot->legend->setRowSpacing(-3);

    for(int i=0; i< legends.size(); i++) {
        ui->myPlot->graph(2*i)->setName(legends[i]);
    }
}

void PlotWidget::addValue(double key, QVector<double> val)
{
    if(!this->connected)
        return;
    for(int i=0; i<(qMin(graphsCount, val.size())); i++) {
          // add data to lines:
          ui->myPlot->graph(2*i)->addData(key, val[i]);
          ui->myPlot->graph(2*i)->removeDataBefore(key-120);  // delete memory after 2 minutes
          ui->myPlot->graph(2*i+1)->clearData();
          ui->myPlot->graph(2*i+1)->addData(key, val[i]);

//          double upper_bound = qMax(val[i] , ui->myPlot->yAxis->range().upper) * 2.0;
//          double lower_bound = qMin(val[i] , ui->myPlot->yAxis->range().lower) * 2.0;

//          ui->myPlot->yAxis->setRangeUpper(upper_bound);
//          ui->myPlot->yAxis->setRangeLower(lower_bound);

//          ui->myPlot->yAxis->setRangeUpper(-3000);
//          ui->myPlot->yAxis->setRangeLower(3000);
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    if(!freezed)
        ui->myPlot->xAxis->setRange(key+4, 20, Qt::AlignRight);
    ui->myPlot->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    frameCount ++;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
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

void PlotWidget::setConnected(bool connected)
{
    this->connected = connected;
}

void PlotWidget::setYAxisRange(double lower, double upper)
{
     ui->myPlot->yAxis->setRange(lower, upper);
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


void PlotWidget::on_closeButton_clicked()
{
    emit closeMe(this->plotName);
}

void PlotWidget::on_minimizeButton_clicked(bool checked)
{
    if(checked) {
        ui->myPlot->hide();
        ui->closeButton->hide();
        ui->pauseButton->hide();
//        emit setMeMinimized(name, true);
        this->resize(100, 40);

    }
    else {
        ui->myPlot->show();
        ui->closeButton->show();
        ui->pauseButton->show();

//        emit setMeMinimized(plotName, true);
    }
}

void PlotWidget::on_pauseButton_clicked(bool checked)
{
    freezed = !checked;
//    this->connected = !checked;
}
