#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include "xbeeprotocol.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent * event);
private slots:
    void readData();
    void on_connect_Button_clicked();

    void on_addRowBtn_clicked();

    void on_startBtn_clicked();

    void on_rmRowBtn_clicked();

    void timer1_update();

    void on_tableWidget_cellChanged(int row, int column);
    void setspeed (int s1,int s2,int s3,int s4);

    void on_stopBtn_clicked();

private:
    void drawChart();
    Ui::MainWindow *ui;
    QTimer *timer1;
    int time = 0;
    int* speeds;
    XBeeProtocol xBeeProtocol;
    int myspeed=0;
    QSerialPort serial;
    QList< QPair< double , double > > data;
};

#endif // MAINWINDOW_H
