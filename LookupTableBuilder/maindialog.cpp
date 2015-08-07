#include "maindialog.h"
#include "ui_maindialog.h"
#include "Dialogs/designdialog.h"
#include <QDebug>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);


}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::on_exit_btn_clicked()
{
    this->close();
    this->deleteLater();
}

void MainDialog::on_output_btn_clicked()
{

}

void MainDialog::on_input_btn_clicked()
{
    DesignDialog* d;
    d = new DesignDialog(this);
    d->show();
    this->hide();

    connect(d, SIGNAL(rejected()),
            this, SLOT(on_child_rejected()));
}

void MainDialog::on_child_rejected(){
    this->show();
}
