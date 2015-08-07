#include "designdialog.h"
#include "ui_designdialog.h"
#include "Controller/filecontroller.h"
#include <QFileDialog>
#include <QList>
#include <QInputDialog>

#include <QDebug>

DesignDialog::DesignDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DesignDialog)
{
    ui->setupUi(this);

    graphView = new GraphView(this);
    graphView->setWH(ui->txtW->text().toInt(), ui->txtH->text().toInt());
    graphView->addGraph();

    ui->graphLayout->addWidget(graphView);
}

DesignDialog::~DesignDialog()
{
    delete graphView;
    delete ui;
}

void DesignDialog::reject(){
    QDialog::reject();
    this->deleteLater();
}

void DesignDialog::on_btnBack_clicked()
{
    exit(1);
    this->reject();
}

void DesignDialog::on_btnSave1_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("SaveFile"),"", tr("Files (*.cryr)"));

    FileController fc;
    fc.setFile(fileName);
    QList<Graph*> graph_list = graphView->getGraphList();
    for(int i=0; i<graph_list.size(); i++) {
        for(int j=0; j<graph_list[i]->getSize(); j++) {
            QVector2D pnt = graph_list[i]->getPoint(j);
            fc.appenPair(pnt.x(), pnt.y());
        }
    }

//    FileController::saveRawData(fileName, list, graphView->getW(), graphView->getH());
}

void DesignDialog::on_btnSave2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("SaveFile"),"", tr("Files (*.cryr)"));

    FileController fc;
    fc.setFile(fileName);
    QList<Graph*> graph_list = graphView->getGraphList();
    for(int i=0; i<graph_list.size(); i++) {
        qreal x_step = ui->intervalSpinBox->value();
        qreal x_start = 0.;
        qreal x_end = graph_list[i]->getPoint(graph_list[i]->getSize() - 1).x();
        for ( int x=x_start; x<x_end; x+= x_step ) {
            QVector2D pnt = graph_list[i]->getFunctionAtX(x);
            fc.appenPair(pnt.x(), pnt.y());
        }
    }
}

void DesignDialog::on_txtH_returnPressed()
{
    QString w = ui->txtW->text();
    QString h = ui->txtH->text();
    graphView->setWH(w.toInt(), h.toInt());
}

void DesignDialog::on_txtW_returnPressed()
{
    QString w = ui->txtW->text();
    QString h = ui->txtH->text();
    graphView->setWH(w.toInt(), h.toInt());
}

void DesignDialog::on_btnReset_clicked()
{
    graphView->removeGraphs();
    graphView->addGraph();
}

void DesignDialog::on_loadBtn_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this);
    FileController fc(this);
    fc.setFile(file_name);

    QList<QVector2D> read_data;
    if(fc.readFile(read_data)) {
//        graphView->removeGraphs();
        graphView->removeGraphs();
        graphView->addGraph();
        Graph* g = graphView->getGraph(0);
        for(int i=0; i<read_data.size(); i++) {
            g->addPoint(read_data[i].x(), read_data[i].y());
        }
        graphView->redraw();
    }

}
