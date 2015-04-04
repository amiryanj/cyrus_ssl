#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableWidgetItem>
#include <QPicture>
#include <QStringList>
#include "selectplotdialog.h"
#include "../server/paramater-manager/parametermanager.h"
#include <string>
#include <QLabel>
#include <QMessageBox>


MainWindow::MainWindow(Color our_color, Side our_side, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ourColor = SSL::Yellow;
    ourColor = our_color;
    field = new FieldScene(ourColor);

    ui->fieldWidgetLayout->addWidget(field);
    scatter = new ScatterPlotWidget(this);
    ui->scatterLayout->addWidget(scatter);

    plotManager = new PlotManagerWidget(this);
    ui->plotManagerLayout->addWidget(plotManager);

    status_strategy = new QLabel(this);
    status_referee = new QLabel(this);
    status_led_game_running = new QLabel(this);

    statusBar()->addWidget(status_led_game_running, 1);
    statusBar()->addWidget(status_referee, 2);
    statusBar()->addWidget(status_strategy, 2);

    receiver = new PacketReceiver();
    parser = new PacketParser();

    connect(receiver, SIGNAL(newWorldPacket(ssl_world_packet)), parser, SLOT(handleWorldPacket(ssl_world_packet)));
    connect(receiver, SIGNAL(newPlannerPacket(ssl_planner_packet)), parser, SLOT(handlePlannerPacket(ssl_planner_packet)));
    connect(receiver, SIGNAL(newAnalyzerPacket(ssl_analyzer_packet)), parser, SLOT(handleAnalyzerPacket(ssl_analyzer_packet)));
    connect(receiver, SIGNAL(newDecisionPacket(ssl_decision_packet)), parser, SLOT(handleDecisionPacket(ssl_decision_packet)));

    connect(parser, SIGNAL(newRobotState(RobotState)), field, SLOT(updateRobotState(RobotState)));
    connect(parser, SIGNAL(newBallState(BallState)), field, SLOT(updateBallState(BallState)));
    connect(parser, SIGNAL(newPlan(int,QVector<RobotState>,QVector3D,QVector3D)),
            field , SLOT(updateRobotPlan(int,QVector<RobotState>,QVector3D,QVector3D)));

    connect(parser, SIGNAL(newRobotState(RobotState)), this, SLOT(updateRobotVelocity(RobotState)));

    connect(parser, SIGNAL(currentStrategy(QString,QMap<int,QString>)), field, SLOT(updateCurrentStrategy(QString,QMap<int,QString>)));
    connect(parser, SIGNAL(currentStrategy(QString,QMap<int,QString>)), this, SLOT(updateCurrentStrategy(QString)));

    connect(parser, SIGNAL(newNearestRobotToBall(int,int,SSL::Color,bool)), field, SLOT(updateNearestRobotToBall(int,int,SSL::Color,bool)));
    connect(parser, SIGNAL(gameRunning(bool)), this, SLOT(setGameRunningState(bool)));
    connect(parser, SIGNAL(newIntersectPoint(float,RobotState)), field, SLOT(updateRobotIntersect(float,RobotState)));
    connect(parser, SIGNAL(newRefereeState(QString)), this, SLOT(setRefereeState(QString)));


    setupTree();
    setupTable();

    ui->actionShow_Plans->setChecked(true);
    ui->actionShow_Targets->setChecked(true);
    ui->actionConnect_Server->setChecked(true);

    ui_settings = new QSettings("../../cyrus2014/settings/ui_settings.ini", QSettings::IniFormat, this);
    ui->splitter_1->restoreState(ui_settings->value("splitter_1").toByteArray());
    ui->splitter_2->restoreState(ui_settings->value("splitter_2").toByteArray());
    ui->splitter_3->restoreState(ui_settings->value("splitter_3").toByteArray());

    resize( ui_settings->value("mainwindow_size").toSize() );
    restoreState( ui_settings->value("mainwindow_state").toByteArray() );
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::joinCyrusServer()
{
    ParameterManager* pm = ParameterManager::getInstance();
    int _port = pm->get<int>("network.VISUALIZER_PORT");
    QString _address = ((string)pm->get<std::string>("network.VISUALIZER_ADDRESS")).c_str();
    receiver->setNetworkSettings(_port, _address);
    return receiver->joinNetwork();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    ui_settings->setValue("mainwindow_size", this->size());
    ui_settings->setValue("mainwindow_state", this->saveState());

    ui_settings->setValue("splitter_1", ui->splitter_1->saveState());
    ui_settings->setValue("splitter_2", ui->splitter_2->saveState());
    ui_settings->setValue("splitter_3", ui->splitter_3->saveState());
}

void MainWindow::setupTable()
{
  {
    // our team
    ui->ourRobotsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ourRobotsTableWidget->setColumnCount(2);
    QStringList ourRobotTableHeaders;
    ourRobotTableHeaders << "Role" << "In Field"; // << "Position";
    ui->ourRobotsTableWidget->setHorizontalHeaderLabels(ourRobotTableHeaders);

    int reducedRows = 4;
    ui->ourRobotsTableWidget->setRowCount(MAX_ID_NUM - reducedRows);

    QStringList ourTableRobotsHeader;
    for (int i=0; i< MAX_ID_NUM - reducedRows; ++i) {
        QString temp = QString((ourColor==SSL::Blue)? "Blue %1":"Yellow %1").arg(i);
        ourTableRobotsHeader << temp;
    }
    ui->ourRobotsTableWidget->setVerticalHeaderLabels(ourTableRobotsHeader);

    for(int i=0; i< MAX_ID_NUM; ++i)
    {
        for(int j=0; j< 4; j++) {
            our_robots[i][j] = new QTableWidgetItem();
            ui->ourRobotsTableWidget->setItem(i, j, our_robots[i][j]);
        }
    }
    for(int i=0; i < ui->ourRobotsTableWidget->rowCount(); i++) {
        ui->ourRobotsTableWidget->setRowHeight(i, 20);
    }
  }
}

void MainWindow::setupTree()
{
    QString tempStr = ((ourColor==SSL::Blue)? QString("Blue"):QString("Yellow"));
    QTreeWidgetItem* ourTeamItem = new QTreeWidgetItem(ui->treeWidget);
    ourTeamItem->setText(0, "Our Team [" + tempStr + "]");

    for(int i=0; i<MAX_TEAM_PLAYER; i++) {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, tempStr + QString(" Robot %1 ").arg(i));
        ourTeamItem->addChild(item);
    }

    tempStr = ((ourColor==SSL::Yellow)? QString("Blue"):QString("Yellow"));
    QTreeWidgetItem* opTeamItem = new QTreeWidgetItem(ui->treeWidget);
    opTeamItem->setText(0, "Opponent Team [" + tempStr + "]");

    for(int i=0; i<MAX_TEAM_PLAYER; i++) {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, tempStr + QString(" Robot %1").arg(i));
        opTeamItem->addChild(item);
    }

}

void MainWindow::updateRobotVelocity(RobotState state)
{
    if(state.color == ourColor)
        ourActualVelocity[state.ID] = QVector3D(state.velocity.X(), state.velocity.Y(), state.velocity.Teta());
}

void MainWindow::on_actionQuit_triggered()
{
//    QMessageBox msgBox(this);
//    msgBox.setText("Do you want to exit?");
//    msgBox.setButtonText(1, "No");
//    msgBox.addButton("Yes", );
//    msgBox.setButtonText(0, "No");
//    if(msgBox.exec() == QDialog::Accepted)
        this->close();
}

void MainWindow::on_actionFull_Screen_toggled(bool arg1)
{
    if(arg1) {
        field->updateZoom(100);
        this->setWindowFlags(Qt::FramelessWindowHint);
        this->showNormal();
        this->showMaximized();
    }
    else {
        this->setWindowFlags(Qt::Window);
        this->showNormal();
    }
}

void MainWindow::setGameRunningState(bool game_running)
{
    if(game_running) {
        ui->gameRunningLabel->setStyleSheet("color:green;");
        ui->gameRunningLabel->setText("Game Running");
    }
    else {
        ui->gameRunningLabel->setStyleSheet("color:red;");
        ui->gameRunningLabel->setText("Game Not Running");
    }

}

void MainWindow::setRefereeState(QString state)
{
    if(state.toLower().contains("blue") && ourColor == SSL::Blue) {
        state.replace("Blue", "Our");
    } else if(state.toLower().contains("blue") && ourColor == SSL::Yellow) {
        state.replace("Blue", "Opponent");
    } else if(state.toLower().contains("yellow") && ourColor == SSL::Blue) {
        state.replace("Yellow", "Opponent");
    } else if(state.toLower().contains("yellow") && ourColor == SSL::Yellow) {
        state.replace("Yellow", "Our");
    }

    QString str = "Referee: " + state;
    ui->refereeLabel->setText(str);
    status_referee->setText(str);

    field->showBallStopZone( state.toLower().contains("stop") );
}

void MainWindow::updateCurrentStrategy(QString strategy_name)
{
    QString str = "Strategy: "+  strategy_name;
    ui->strategyLabel->setText(str);
    status_strategy->setText(str);
}
void MainWindow::on_actionShowIntersects_toggled(bool arg1)
{
    field->setIsShowingIntersects(arg1);
}

void MainWindow::on_actionShow_Plans_toggled(bool arg1)
{
    field->setIsShowingPlans(arg1);
}

void MainWindow::on_actionConnect_Server_triggered(bool checked)
{
    if(checked) {
        joinCyrusServer();
        receiver->timer.start();
    }

    else {
        receiver->timer.stop();
        receiver->disconnectNetwork();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    e->ignore();
}
