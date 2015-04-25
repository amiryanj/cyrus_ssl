#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "plot-manager/plotmanagerwidget.h"
#include "fieldscene.h"
#include "packetparser.h"
#include <QMap>
#include <QSettings>
#include <QTreeWidgetItem>

#include "robotpropertieswidget.h"
#include "packetreceiver.h"
#include "plot-manager/scatterplotwidget.h"

class QTableWidgetItem;
class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(SSL::Color our_color, SSL::Side our_side, QWidget *parent = 0);
    ~MainWindow();

    SSL::Color ourColor;
    bool joinCyrusServer();

private slots:
    void closeEvent(QCloseEvent *e);

    void setupTable();

    void setupTree();

    void updateRobotVelocity(RobotState state);

    void on_actionQuit_triggered();

    void on_actionFull_Screen_toggled(bool arg1);

    void setGameRunningState(bool game_running);

    void setRefereeState(QString state);

    void updateCurrentStrategy(QString strategy_name);

    void on_actionShowIntersects_toggled(bool arg1);

    void on_actionShow_Plans_toggled(bool arg1);

    void on_actionConnect_Server_triggered(bool checked);

    void mouseMoveEvent(QMouseEvent *e);

private:

    QSettings *ui_settings;
    QLabel* status_strategy;
    QLabel* status_referee;
    QLabel* status_led_game_running;

    Ui::MainWindow *ui;
    FieldScene *field;
    PacketReceiver *receiver;
    PlotManagerWidget* plotManager;

    PacketParser *parser;
    QTableWidgetItem* our_robots[MAX_ID_NUM][4];
    QTableWidgetItem* op_robots[MAX_ID_NUM][4];

    QVector3D ourActualVelocity[MAX_ID_NUM];

    QHBoxLayout mainHLayout;
    QVBoxLayout leftVLayout;
    QVBoxLayout middleVLayout;
    QVBoxLayout rightVLayout;

    ScatterPlotWidget* scatter;

};

#endif // MAINWINDOW_H
