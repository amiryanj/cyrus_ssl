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
    currentFolder = "../../";
    fileName = "";
    this->resize(1000, 600);
}

DesignDialog::~DesignDialog()
{
    delete graphView;
    delete ui;
}

void DesignDialog::reject()
{
    QDialog::reject();
    this->deleteLater();
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

void DesignDialog::on_openBtn_clicked()
{
    QString name_ = QFileDialog::getOpenFileName(this,
                                                 "Open Lookup Table",
                                                 currentFolder,
                                                 "Tables (*.txt *.csv)");
    if(name_.isEmpty())
        return;

    this->fileName = name_;
    FileController fc;
    fc.setFile(fileName);

    QList<QVector2D> read_data;
    if(fc.readFile(read_data)) {
        graphView->removeGraphs();
        Graph* g = graphView->addGraph();
        double min_x=0, max_x=0;
        double min_y=0, max_y=0;
        for(int i=0; i<read_data.size(); i++) {
            g->addPoint(read_data[i].x(), read_data[i].y());
            max_x = qMax((double)read_data[i].x(), max_x);
            max_y = qMax((double)read_data[i].y(), max_y);
        }
        QRect r(0, -max_y, (max_x-min_x), 2*(max_y-min_y));
        graphView->setWH(r);
    }
}

void DesignDialog::on_saveButton_clicked()
{
    if(fileName.isEmpty()) {
        QString name_ = QFileDialog::getSaveFileName(this,
                                                tr("Save File"),
                                                currentFolder,
                                                tr("CSV Files (*.csv)"));
        if(name_.length() == 0)
            return;
        if(!name_.endsWith(".csv"))
            name_.append(".csv");
        fileName = name_;
    }
    save();
}

void DesignDialog::on_saveAsBtn_clicked()
{
    QString name_ = QFileDialog::getSaveFileName(this,
                                                    tr("Save File"),
                                                    currentFolder,
                                                    tr("CSV Files (*.csv)"));
    if(name_.isEmpty())
        return;
    if(!name_.endsWith(".csv"))
        name_.append(".csv");
    fileName = name_;
    save();
}

void DesignDialog::save()
{
    QList<Graph*> graph_list = graphView->getGraphList();

    FileController fc;
    fc.setFile(fileName);
    fc.clearFile();
    for(int i=0; i<graph_list.size(); i++) {
        for(int j=0; j<graph_list[i]->getSize(); j++) {
            QVector2D pnt = graph_list[i]->getPoint(j);
            fc.appenPair(pnt.x(), pnt.y());
        }
    }

    fc.setFile(fileName.left(fileName.lastIndexOf(".")) + ".tbl");
    fc.clearFile();
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

void DesignDialog::on_resetBtn_clicked()
{
    fileName = "";
    graphView->removeGraphs();
    graphView->addGraph();
}

void DesignDialog::on_quitBtn_clicked()
{
    exit(1);
}
