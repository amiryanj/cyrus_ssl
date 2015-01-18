#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <string>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(&serial, SIGNAL(readyRead()), this, SLOT(readData()));
    setFocusPolicy(Qt::StrongFocus);
    QList<QSerialPortInfo> serials = QSerialPortInfo::availablePorts();
    ui->setupUi(this);
    for(int i = 0 ; i < serials.size() ; i++)
    {

       ui->comboBox->addItem(serials[i].portName());
    }
    ui->customplot->setInteraction(QCP::iRangeDrag,true);
    ui->customplot->setInteraction(QCP::iRangeZoom,true);
    QTableWidgetItem *item = new QTableWidgetItem(tr("%1,%2").arg("salam","golabi"));
    ui->tableWidget->insertRow(4);
    ui->tableWidget->setItem(0,0,item);
    speeds=new int[4];
    speeds[0]=speeds[1]=speeds[2]=speeds[3]=0;

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::readData()
{
    QByteArray data=serial.readAll();
    qDebug(data);
}
void MainWindow::on_connect_Button_clicked()
{
    if(!serial.isOpen())
    {
        serial.setPortName(ui->comboBox->currentText());
        serial.setBaudRate(38400);

        if(serial.open(QIODevice::ReadWrite))
        {
            ui->status_Lable->setText("Connected");
            ui->connect_Button->setText("Disconnect");
        }
    }else
    {
        ui->status_Lable->setText("Not Connected");
        ui->connect_Button->setText("Connect");
        serial.close();
    }
}

void MainWindow::on_addRowBtn_clicked()
{
    data.append(qMakePair(0.0,0.0));
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    drawChart();
}

void MainWindow::on_startBtn_clicked()
{
    timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(timer1_update()));
    time = 0;
    timer1->start(100);
}
void MainWindow::drawChart()
{
    QCustomPlot *plot;
    plot = ui->customplot;
    plot->clearItems();
    plot->addGraph();
    QVector< double > x(0) , y(0);
    for(int i = 0 ; i < data.size(); i++)
    {
        x.append(data[i].first);
        y.append(data[i].second);
    }
    plot->graph(0)->setData(x,y);
    plot->replot();

}
void MainWindow::on_rmRowBtn_clicked()
{
    //if(ui->tableWidget->selectedItems()[0]->row())
    if(ui->tableWidget->selectedItems().size() > 0)
    {
        data.removeAt(ui->tableWidget->selectedItems()[0]->row());
        ui->tableWidget->removeRow(ui->tableWidget->selectedItems()[0]->row());
        drawChart();
    }
}

void MainWindow::timer1_update()
{

    /*double val=0;
    for(int i = 0 ; i < data.size() ; i++)
    {
        if(time / 1000.0 > data[i].first) // maybe  (time / 1000.0 => data[i].first)
            val = data[i].second; // caculating speed
    }
    qDebug() <<QString::number(time) <<" " << QString::number(val) << endl;
    time+=timer1->interval();*/
    int sends[] = {speeds[0], speeds[1],speeds[2],speeds[3],ui->spinBox_1->value(),ui->spinBox_2->value(),ui->spinBox_3->value()};
    QString s="";
    for(int i =0  ; i < 7 ; i++)
    {
        s+=QString::number(sends[i]) +" ";
    }

    qDebug() << s ;
    char *o=xBeeProtocol.MakePacket(sends);
    s="";
    for(int i =0  ; i < 10 ; i++)
    {
        s+=QString::number(o[i]) +" ";
    }
    qDebug() << s ;
    serial.write(o,9);


}
void MainWindow::keyPressEvent(QKeyEvent * event){
    QString drive ="";
    drive+=event->key();
    qDebug()<<drive;
    int myspeed= ui->spinBox_4->value();
    if (drive == "+")
    {
        myspeed+=10;
    }
    if (drive == "-")
    {
        myspeed -= 10;
    }
    myspeed = myspeed % 255;
    if (drive == "W")
    {
        setspeed(myspeed, myspeed, -myspeed, -myspeed);
    }
    if (drive == "S")
    {
        setspeed(-myspeed, -myspeed, myspeed, myspeed);
    }
    if (drive == "D")
    {
        setspeed(-myspeed, myspeed, myspeed, -myspeed);
    }
    if (drive == "A")
    {
        setspeed(myspeed, (int)-1.5*myspeed, (int)-1.5*myspeed, myspeed);
    }
    if (drive == "Q")
    {
        setspeed(50, 50, 50, 50);
    }
    if (drive == "E")
    {
        setspeed(-50, -50, -50, -50);
    }
    if (drive != "")
    {
        //timer3.Enabled = true;
        // controller.reset();
    }
    if (drive == " ")
    {
        setspeed(0, 0, 0, 0);
        // timer3.Enabled = false;
    }
    ui->spinBox_4->setValue(myspeed);
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    if(column == 0)
        data[row].first = ui->tableWidget->item(row,column)->text().toDouble();
    if(column == 1)
        data[row].second = ui->tableWidget->item(row,column)->text().toDouble();
    drawChart();
}

void MainWindow::on_stopBtn_clicked()
{

    if(timer1 != NULL && timer1->isActive())
    {
        timer1->stop();
        time = 0;
    }
}
void MainWindow::setspeed(int s1, int s2, int s3, int s4)
{
    speeds[0]=s1;
    speeds[1]=s2;
    speeds[2]=s3;
    speeds[3]=s4;

}
