#include "robotpropertieswidget.h"
#include "ui_robotpropertieswidget.h"
#include "plotwidget.h"

RobotPropertiesWidget::RobotPropertiesWidget(bool isOurs, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RobotPropertiesWidget)
{
    ui->setupUi(this);
    int num_graphs = (isOurs)? 3:1;
    PlotWidget* xpWidget = new PlotWidget(num_graphs, ui->xPlotWidget);
    PlotWidget* ypWidget = new PlotWidget(num_graphs, ui->yPlotWidget);
    PlotWidget* wpWidget = new PlotWidget(num_graphs, ui->tetaPlotWidget);
    PlotWidget* magpWidget = new PlotWidget(num_graphs, ui->magPlotWidget);


}

RobotPropertiesWidget::~RobotPropertiesWidget()
{
    delete ui;
}
