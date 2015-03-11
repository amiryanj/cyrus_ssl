#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "../../visualizer/plotwidget.h"
#include "../ai/SSLWorldModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void timerOVF();
    
private:
    Ui::MainWindow *ui;
    PlotWidget *pw_;
    QTimer timer;
};

#endif // MAINWINDOW_H
