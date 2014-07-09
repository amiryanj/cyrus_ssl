#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "plotwidget.h"
#include "fieldscene.h"
#include "packetparser.h"
#include <QMap>
#include <QTreeWidgetItem>

#include "robotpropertieswidget.h"
#include "packetreceiver.h"

class QTableWidgetItem;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(SSL::Color our_color, SSL::Side our_side, QWidget *parent = 0);
    ~MainWindow();

    PlotWidget* addPlot(uint graph_num, QString label = "Unlabeled");
    
    SSL::Color ourColor;
    bool joinCyrusServer();

private slots:
    void setupTable();

    void setupTree();

    void updateRobotVelocity(RobotState state);

    void plotRobotVelocity(int id, QVector3D desired, QVector3D applied);

    void on_ourRobotsTableWidget_cellDoubleClicked(int row, int column);

    void on_tabWidget_tabCloseRequested(int index);

    void on_opRobotsTableWidget_cellDoubleClicked(int row, int column);

    void on_actionQuit_triggered();

    void on_actionConnect_Server_triggered();

    void on_actionFull_Screen_toggled(bool arg1);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void plotBallvelocity(BallState state);

    void setGameRunningState(bool game_running);

    void setRefereeState(QString state);

    void updateCurrentStrategy(QString strategy_name);

    void on_actionShowIntersects_toggled(bool arg1);

    void on_actionShow_Plans_toggled(bool arg1);

    void on_actionConnect_Server_triggered(bool checked);

private:

    Ui::MainWindow *ui;
    FieldScene *field;
    PacketReceiver *receiver;
    QMap<QString, PlotWidget*> plotList;
    QMap<QString, RobotPropertiesWidget*> robotWidgetList;

    PacketParser *parser;
    QTableWidgetItem* our_robots[MAX_ID_NUM][4];
    QTableWidgetItem* op_robots[MAX_ID_NUM][4];

    QVector3D ourActualVelocity[MAX_ID_NUM];

    QHBoxLayout mainHLayout;
    QVBoxLayout leftVLayout;
    QVBoxLayout middleVLayout;
    QVBoxLayout rightVLayout;

};

#endif // MAINWINDOW_H
