#include "selectplotdialog.h"
#include "ui_selectplotdialog.h"

SelectPlotDialog::SelectPlotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectPlotDialog)
{
    ui->setupUi(this);
}

SelectPlotDialog::~SelectPlotDialog()
{
    delete ui;
}

bool SelectPlotDialog::is_x_selected()
{
    return ui->x_radioButton->isChecked();
}

bool SelectPlotDialog::is_y_selected()
{
    return ui->y_radioButton->isChecked();
}

bool SelectPlotDialog::is_mag_selected()
{
    return ui->mag_radioButton->isChecked();
}

bool SelectPlotDialog::is_teta_selected()
{
    return ui->teta_radioButton->isChecked();
}



