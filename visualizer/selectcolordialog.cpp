#include "selectcolordialog.h"
#include "ui_selectcolordialog.h"

SelectColorDialog::SelectColorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectColorDialog)
{
    ui->setupUi(this);
}

SelectColorDialog::~SelectColorDialog()
{
    delete ui;
}

SSL::Color SelectColorDialog::getOurColor()
{
    if(ui->colorComboBox->currentText().toLower() == "blue")
        return SSL::Blue;
    else
        return SSL::Yellow;
}

SSL::Side SelectColorDialog::getOurSide()
{
    if(ui->sideComboBox->currentText().toLower() == "left")
        return SSL::Left;
    else
        return SSL::Right;
}

void SelectColorDialog::setStatusText(QString status)
{
    ui->statusLabel->setText(status);
}
