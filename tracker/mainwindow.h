#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "../server/ai/SSLWorldModel.h"
#include "../server/vision/VisionFilter.h"
#include "../server/vision/BallFilter.h"

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
    QTimer timer;

};

#endif // MAINWINDOW_H
