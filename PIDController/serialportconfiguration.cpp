#include "serialportconfiguration.h"
#include "ui_serialportconfiguration.h"

SerialPortConfiguration::SerialPortConfiguration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialPortConfiguration)
{
    ui->setupUi(this);
}

SerialPortConfiguration::~SerialPortConfiguration()
{
    delete ui;
}
