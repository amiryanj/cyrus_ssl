#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableWidgetItem>
#include <QPicture>
#include <QStringList>
#include "selectplotdialog.h"

MainWindow::MainWindow(Color our_color, Side our_side, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ourColor = SSL::Yellow;
    ourColor = our_color;
    field = new FieldScene(ourColor);

    ui->fieldWidgetLayout->addWidget(field);

    receiver = new PacketReceiver();

    parser = new PacketParser();

    connect(receiver, SIGNAL(newWorldPacket(ssl_world_packet)), parser, SLOT(handleWorldPacket(ssl_world_packet)));
    connect(receiver, SIGNAL(newPlannerPacket(ssl_planner_packet)), parser, SLOT(handlePlannerPacket(ssl_planner_packet)));
    connect(receiver, SIGNAL(newAnalyzerPacket(ssl_analyzer_packet)), parser, SLOT(handleAnalyzerPacket(ssl_analyzer_packet)));
    connect(receiver, SIGNAL(newDecisionPacket(ssl_decision_packet)), parser, SLOT(handleDecisionPacket(ssl_decision_packet)));

    connect(parser, SIGNAL(newRobotState(RobotState)), field, SLOT(updateRobotState(RobotState)));
    connect(parser, SIGNAL(newBallState(BallState)), field, SLOT(updateBallState(BallState)));
    connect(parser, SIGNAL(newPlan(int,QVector<RobotState>,QVector3D,QVector3D)), field, SLOT(updateRobotPlan(int,QVector<RobotState>,QVector3D,QVector3D)));

    connect(parser, SIGNAL(newRobotState(RobotState)), this, SLOT(updateRobotVelocity(RobotState)));
    connect(parser, SIGNAL(newRobotVelocity(int,QVector3D,QVector3D)), this, SLOT(plotRobotVelocity(int,QVector3D,QVector3D)));
    connect(parser, SIGNAL(newBallState(BallState)), this, SLOT(plotBallvelocity(BallState)));

    connect(parser, SIGNAL(currentStrategy(QString,QMap<int,QString>)), field, SLOT(updateCurrentStrategy(QString,QMap<int,QString>)));
    connect(parser, SIGNAL(currentStrategy(QString,QMap<int,QString>)), this, SLOT(updateCurrentStrategy(QString)));

    connect(parser, SIGNAL(newNearestRobotToBall(int,int,SSL::Color,bool)),  field,SLOT(updateNearestRobotToBall(int,int,SSL::Color,bool)));
    connect(parser, SIGNAL(gameRunning(bool)), this, SLOT(setGameRunningState(bool)));
    connect(parser, SIGNAL(newIntersectPoint(float,RobotState)), field, SLOT(updateRobotIntersect(float,RobotState)));
    connect(parser, SIGNAL(newRefereeState(QString)), this, SLOT(setRefereeState(QString)));


    setupTree();
    setupTable();

    ui->actionShow_Plans->setChecked(true);
    ui->actionShow_Targets->setChecked(true);
    ui->actionConnect_Server->setChecked(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

PlotWidget* MainWindow::addPlot(uint graph_num, QString label)
{
    PlotWidget *plot = new PlotWidget(graph_num, ui->tabWidget);

    ui->tabWidget->addTab(plot, label);

    return plot;
}

bool MainWindow::joinCyrusServer()
{
    return receiver->joinNetwork(VISUALIZER_IP, VISUALIZER_PORT);
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


    // op team
  {
//    ui->opRobotsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->opRobotsTableWidget->setColumnCount(2);
//    QStringList opRobotTableHeaders;
//    opRobotTableHeaders << "Role" << "In Field" ; //<< "Position";
//    ui->opRobotsTableWidget->setHorizontalHeaderLabels(opRobotTableHeaders);

//    int reducedRows = 4;
//    ui->opRobotsTableWidget->setRowCount(MAX_ID_NUM - reducedRows);

//    QStringList opTableRobotsHeader;
//    for (int i=0; i< MAX_ID_NUM - reducedRows; ++i) {
//        QString temp = QString((ourColor==SSL::Blue)? "Yellow %1":"Blue %1").arg(i);
//        opTableRobotsHeader << temp;
//    }
//    ui->opRobotsTableWidget->setVerticalHeaderLabels(opTableRobotsHeader);

//    for(int i=0; i< MAX_ID_NUM; ++i)
//    {
//        for(int j=0; j< 4; j++) {
//            op_robots[i][j] = new QTableWidgetItem();
//            ui->opRobotsTableWidget->setItem(i, j, op_robots[i][j]);
//        }
//    }

//    for(int i=0; i<ui->opRobotsTableWidget->rowCount(); i++) {
//        ui->opRobotsTableWidget->setRowHeight(i, 20);
//    }
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

void MainWindow::on_ourRobotsTableWidget_cellDoubleClicked(int row, int column)
{
    QString plotName = QString((ourColor==SSL::Blue)?"Blue%1 ":"Yellow%1 ").arg(row);
    SelectPlotDialog dialog;
    if(dialog.exec() == QDialog::Accepted) {
        if(dialog.is_x_selected())
            plotName.append("X");
        if(dialog.is_y_selected())
            plotName.append("Y");
        if(dialog.is_mag_selected())
            plotName.append("M");
        if(dialog.is_teta_selected())
            plotName.append("T");
    }

    PlotWidget* plot;
    if(!plotList.contains(plotName))
        plot = addPlot(3, plotName);
    else
        plot = plotList[plotName];
    ui->tabWidget->setCurrentWidget(plot);
    this->plotList.insert(plotName, plot);
}

void MainWindow::on_opRobotsTableWidget_cellDoubleClicked(int row, int column)
{
    QString plotName = QString((ourColor==SSL::Yellow)?"Blue%1 ":"Yellow%1 ").arg(row);
    SelectPlotDialog dialog;
    if(dialog.exec() == QDialog::Accepted) {
        if(dialog.is_x_selected())
            plotName.append("X");
        if(dialog.is_y_selected())
            plotName.append("Y");
        if(dialog.is_mag_selected())
            plotName.append("M");
        if(dialog.is_teta_selected())
            plotName.append("T");
    }


    PlotWidget* plot;
    if(!plotList.contains(plotName))
        plot = addPlot(3, plotName);
    else
        plot = plotList[plotName];
    ui->tabWidget->setCurrentWidget(plot);
    this->plotList.insert(plotName, plot);
}

void MainWindow::updateRobotVelocity(RobotState state)
{
    if(state.color == ourColor)
        ourActualVelocity[state.ID] = QVector3D(state.velocity.X(), state.velocity.Y(), state.velocity.Teta());
}

void MainWindow::plotRobotVelocity(int id, QVector3D desired, QVector3D applied)
{
    QStringList str_list;
    str_list << "X" << "Y" << "M" << "T";
    for(int i = 0 ; i < str_list.size() ; i++)
    {
        QString str = ((ourColor==SSL::Blue)? "Blue":"Yellow") + QString::number(id) + " " + str_list[i];
        if(plotList.contains(str))
        {
            PlotWidget* plot = plotList[QString("%1").arg(str)];
            QVector<double> values;
            if(str_list.at(i) == "X")
                values << ourActualVelocity[id].x() << desired.x() << applied.x() ;
            else if(str_list.at(i) == "Y")
                values << ourActualVelocity[id].y() << desired.y() << applied.y() ;
            else if(str_list.at(i) == "M")
                values << ourActualVelocity[id].toVector2D().length() << desired.toVector2D().length() << applied.toVector2D().length() ;
             else if(str_list.at(i) == "Y")
                values << ourActualVelocity[id].z() << desired.z() << applied.z() ;
            plot->addValue(QDateTime::currentDateTime().toTime_t()+ QTime::currentTime().msec()/1000.0, values);
        }
    }
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    QString tab_text = ui->tabWidget->tabText(index);
    this->plotList.remove(tab_text);
    ui->tabWidget->removeTab(index);

    // TO DO
    // delete the plot widget that would be closed
//    ui->tabWidget->
//    this->plotList
}

void MainWindow::on_actionQuit_triggered()
{
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

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QString a = item->text(column);
    qDebug() << "Salam:   " << a;
    if(a.contains("Robot")) {
        RobotPropertiesWidget *widget = new RobotPropertiesWidget();
        ui->tabWidget->addTab(widget, a);
        this->robotWidgetList.insert(a, widget);
    }
//    if(item->)
}

void MainWindow::plotBallvelocity(BallState state)
{
    if(!plotList.contains("ball_x")) {
        PlotWidget* plot = addPlot(1, "ball_x");
        plotList.insert("ball_x", plot);
    }
    {
    QVector<double> values;
    values << state.velocity.X();
    plotList["ball_x"]->addValue(QDateTime::currentDateTime().toTime_t()+ QTime::currentTime().msec()/1000.0, values);
    }

    if(!plotList.contains("ball_y")) {
        PlotWidget* plot = addPlot(1, "ball_y");
        plotList.insert("ball_y", plot);
    }
    {
    QVector<double> values;
    values << state.velocity.Y();
    plotList["ball_y"]->addValue(QDateTime::currentDateTime().toTime_t()+ QTime::currentTime().msec()/1000.0, values);
    }

    if(!plotList.contains("ball_mag")) {
        PlotWidget* plot = addPlot(1, "ball_mag");
        plotList.insert("ball_mag", plot);
    }
    {
    QVector<double> values;
    values << state.velocity.lenght();
    plotList["ball_mag"]->addValue(QDateTime::currentDateTime().toTime_t()+ QTime::currentTime().msec()/1000.0, values);
    }

    if(!plotList.contains("ball_teta")) {
        PlotWidget* plot = addPlot(1, "ball_teta");
        plotList.insert("ball_teta", plot);
    }
    {
    QVector<double> values;
    values << state.velocity.arctan();
    plotList["ball_teta"]->addValue(QDateTime::currentDateTime().toTime_t()+ QTime::currentTime().msec()/1000.0, values);
    }

    if(!plotList.contains("ball_displacement")) {
        PlotWidget* plot = addPlot(1, "ball_displacement");
        plotList.insert("ball_displacement", plot);
    }
    {
    QVector<double> values;
    values << state.displacement.lenght();
    plotList["ball_displacement"]->addValue(QDateTime::currentDateTime().toTime_t()+ QTime::currentTime().msec()/1000.0, values);
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
    ui->refereeLabel->setText("Referee: " + state);
    field->showBallStopZone( state.toLower().contains("stop") );
}

void MainWindow::updateCurrentStrategy(QString strategy_name)
{
    ui->strategyLabel->setText("Strategy: "+  strategy_name);
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
