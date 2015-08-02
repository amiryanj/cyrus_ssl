#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include "../server/ai/SSLWorldModel.h"
#include "../server/vision/visionfilter.h"
#include "../server/vision/ballfilter.h"
#include "../visualizer/plot-manager/plotmanagerwidget.h"

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
    
    void on_actionPlayStop_toggled(bool arg1);

private:
    Ui::MainWindow *ui;
    PlotManagerWidget* PMW;
    QTimer timer;

};

#endif // MAINWINDOW_H
