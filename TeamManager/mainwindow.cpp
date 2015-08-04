#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow* MainWindow::instance = NULL;
bool MainWindow::on = false;

MainWindow *MainWindow::getInstance()
{
    on = true;
    if(instance == NULL)
        instance = new MainWindow();
    return instance;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupGUIConnections();
    initGUI();
    ui_settings = new QSettings("../../cyrus2014/settings/team_manager_ui_settings.ini", QSettings::IniFormat, this);
    ui_settings->sync();
    //  Info: "Cyrus Robotics", "Cyrus Team Manager", this

    ui->splitter_1->restoreState(ui_settings->value("splitter_1").toByteArray());
    ui->splitter_2->restoreState(ui_settings->value("splitter_2").toByteArray());
//    ui->splitter_3->restoreState(ui_settings->value("splitter_3").toByteArray());

    resize( ui_settings->value("mainwindow_size").toSize() );
    restoreState( ui_settings->value("mainwindow_state").toByteArray() );
    isMainToolBarPinned = ui_settings->value("main_toolbar_pinned").toBool();

    // trick
    isMainToolBarPinned = !isMainToolBarPinned;
    handlePinMainToolBarBtn();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGUI()
{
    ui->chooseTeamColorBlueRB->setChecked(true);
    ui->chooseTeamSideLeftRB->setChecked(true);

    ui->chooseSourceSSLVisionRB->setChecked(true);

    setEnabledLogControlPanel(false);
    setEnabledShowItemButtons(false);

    ui->actionWatch->setEnabled(true);
    setCurrentTabTo(e_TabWatch);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->showNormal();
    this->showMaximized();


    watchField = new WatchFieldGraphics();
    ui->fieldContainerLayout->addWidget(watchField);

    PMW = new PlotManagerWidget(this);
    ui->plotterLayout->addWidget(PMW);
//    ui->plotsContainerWg->layout()->addWidget(PMW);
//    PMW->
}

void MainWindow::setupGUIConnections()
{
    connect(ui->chooseSourceSSLVisionRB, SIGNAL(released()), this, SLOT(handleChoosingVisionSource()));
    connect(ui->chooseSourceCyrusRB, SIGNAL(released()), this, SLOT(handleChoosingVisionSource()));
    connect(ui->chooseSourceGRSimRB, SIGNAL(released()), this, SLOT(handleChoosingVisionSource()));
    connect(ui->chooseSourceLogFileRB, SIGNAL(released()), this, SLOT(handleChoosingVisionSource()));

    connect(ui->actionWatch, SIGNAL(triggered()), this, SLOT(handleChangingMainTab()));
    connect(ui->actionCommnad, SIGNAL(triggered()), this, SLOT(handleChangingMainTab()));
    connect(ui->actionDesign, SIGNAL(triggered()), this, SLOT(handleChangingMainTab()));
    connect(ui->actionAI, SIGNAL(triggered()), this, SLOT(handleChangingMainTab()));
    connect(ui->actionHardware, SIGNAL(triggered()), this, SLOT(handleChangingMainTab()));

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quitProgram()));
    connect(ui->actionMaximize, SIGNAL(triggered(bool)), this, SLOT(showMaximized()));
    connect(ui->actionMinimize, SIGNAL(triggered(bool)), this, SLOT(showMinimized()));

    connect(ui->pinMainToolsTB, SIGNAL(released()), this, SLOT(handlePinMainToolBarBtn()));
}

void MainWindow::handleChoosingVisionSource()
{
    if(ui->chooseSourceSSLVisionRB->isChecked()) {
        setEnabledLogControlPanel(false);
        setEnabledShowItemButtons(false);
    }
    else if(ui->chooseSourceCyrusRB->isChecked()) {
        setEnabledLogControlPanel(false);
        setEnabledShowItemButtons(true);
    }
    else if(ui->chooseSourceGRSimRB->isChecked()) {
        setEnabledLogControlPanel(false);
        setEnabledShowItemButtons(false);
    }
    else if(ui->chooseSourceLogFileRB->isChecked()) {
        setEnabledLogControlPanel(true);
        setEnabledShowItemButtons(false);
    }
}

void MainWindow::setEnabledLogControlPanel(bool enabled_)
{
    // TODO : first check for other conditions
    // if any file is selected?
    // if the file is playable
    // if there is a previous frame
    // if there is a next frame
    // if it is playing or not
    ui->logPlayTB->setEnabled(enabled_);
    ui->logPauseTB->setEnabled(enabled_);
    ui->logStepForwardTB->setEnabled(enabled_);
    ui->logStepBackwardTB->setEnabled(enabled_);

    ui->logSeekPlayingHSl->setEnabled(enabled_);
    ui->logTimeLcd->setEnabled(enabled_);
    ui->logFileNameLE->setEnabled(enabled_);
    ui->logFilebrowseTB->setEnabled(enabled_);
}

void MainWindow::setEnabledShowItemButtons(bool enabled_)
{
    ui->showAgentsTargetTB->setEnabled(enabled_);
    ui->showAgentsPathPlanTB->setEnabled(enabled_);
    ui->showAgentsTimeOfAccessBallTB->setEnabled(enabled_);
    ui->showAgentsOpenAnglesToGoalTB->setEnabled(enabled_);
    ui->showAgentVelocityVectorTB->setEnabled(enabled_);

    ui->showBallOpenAnglesToGoalTB->setEnabled(enabled_);
    ui->showBallVelocityVectorTB->setEnabled(enabled_);

    ui->showFieldRiskyTilesTB->setEnabled(enabled_);
}

void MainWindow::handleChangingMainTab()
{
    QAction* act_ = dynamic_cast<QAction*>(sender());
    if(act_ == ui->actionWatch) {
        // TODO : chech that if there is no other condition for changing the current tab
        if(currentTab != e_TabWatch || ui->outerMainToolContainerWg->isHidden()) {
            setCurrentTabTo(e_TabWatch);
        }
        else if(!isMainToolBarPinned){
            ui->outerMainToolContainerWg->hide();
        }
        else {
            ui->actionWatch->setChecked(true);
        }
    }
    else if(act_ == ui->actionCommnad) {
        if(currentTab != e_TabCommand || ui->outerMainToolContainerWg->isHidden()) {
            setCurrentTabTo(e_TabCommand);
        }
        else if(!isMainToolBarPinned){
            ui->outerMainToolContainerWg->hide();
        }
        else {
            ui->actionCommnad->setChecked(true);
        }
    }
    else if(act_ == ui->actionDesign) {
        if(currentTab != e_TabDesign || ui->outerMainToolContainerWg->isHidden()) {
            setCurrentTabTo(e_TabDesign);
        }
        else if(!isMainToolBarPinned){
            ui->outerMainToolContainerWg->hide();
        }
        else {
            ui->actionDesign->setChecked(true);
        }
    }
    else if(act_ == ui->actionAI) {
        if(currentTab != e_TabAI || ui->outerMainToolContainerWg->isHidden()) {
            setCurrentTabTo(e_TabAI);
        }
        else if(!isMainToolBarPinned){
            ui->outerMainToolContainerWg->hide();
        }
        else {
            ui->actionAI->setChecked(true);
        }
    }
    else if(act_ == ui->actionHardware) {
        if(currentTab != e_TabHardware || ui->outerMainToolContainerWg->isHidden()) {
            setCurrentTabTo(e_TabHardware);
        }
        else if(!isMainToolBarPinned){
            ui->outerMainToolContainerWg->hide();
        }
        else {
            ui->actionHardware->setChecked(true);
        }
    }
    else { // Null
        qDebug("tab change has been invoked from an unknown source");
    }
}

void MainWindow::setCurrentTabTo(MainWindow::MainTab tab_)
{
    // it is a double check
//    if(tab_ == currentTab) {
//        qDebug("Trying to select the same active tab !!!");
//        return;
//    }

    ui->outerMainToolContainerWg->show();

    ui->actionWatch->setChecked(false);
    ui->actionCommnad->setChecked(false);
    ui->actionDesign->setChecked(false);
    ui->actionAI->setChecked(false);
    ui->actionHardware->setChecked(false);


    switch (tab_) {

    case e_TabWatch:
        ui->actionWatch->setChecked(true);
        ui->mainToolsSW->setCurrentWidget(ui->watchToolsPage_1);

        ui->mainWidgetsSW->setCurrentWidget(ui->fieldMainWidget_1_2);
        ui->fieldContainerWg->show();
        ui->messageDisplayingContainerWg->show();
        ui->localRefereeBoxContainterWg->hide();

        ui->plotsContainerWg->hide();        
        break;

    case e_TabCommand:
        ui->actionCommnad->setChecked(true);
        ui->mainToolsSW->setCurrentWidget(ui->commandToolsPage_2);

        ui->mainWidgetsSW->setCurrentWidget(ui->fieldMainWidget_1_2);
        ui->fieldContainerWg->show();
        ui->messageDisplayingContainerWg->hide();
        ui->localRefereeBoxContainterWg->show();

        ui->plotsContainerWg->show();
        break;

    case e_TabDesign:
        ui->actionDesign->setChecked(true);
        ui->mainToolsSW->setCurrentWidget(ui->designToolsPage_3);

        ui->mainWidgetsSW->setCurrentWidget(ui->designMainWidget_3);
        ui->plotsContainerWg->hide();
        break;

    case e_TabAI:
        ui->actionAI->setChecked(true);
        ui->mainToolsSW->setCurrentWidget(ui->aiToolsPage_4);

        ui->mainWidgetsSW->setCurrentWidget(ui->aiMainWidget_4);
        ui->plotsContainerWg->show();
        break;

    case e_TabHardware:
        ui->actionHardware->setChecked(true);
        ui->mainToolsSW->setCurrentWidget(ui->hardwareToolsPage_5);

        ui->mainWidgetsSW->setCurrentWidget(ui->hardwareMainWidget_5);
        ui->plotsContainerWg->hide();
        break;

    default: // none of the available tabs !!!
        break;
    }
    currentTab = tab_;
}

void MainWindow::handlePinMainToolBarBtn()
{
    if(isMainToolBarPinned) {
        isMainToolBarPinned = false;

        ui->outerMainToolContainerWg->hide();

        ui->actionWatch->setChecked(false);
        ui->actionCommnad->setChecked(false);
        ui->actionDesign->setChecked(false);
        ui->actionAI->setChecked(false);
        ui->actionHardware->setChecked(false);

        ui->pinMainToolsTB->setIcon(QIcon(":/icons/min-max-close/pin-icon.png"));

        // TODO : current tab name should be underlined (stylesheet)
    }
    else {
        isMainToolBarPinned = true;
        ui->pinMainToolsTB->setIcon(QIcon(":/icons/min-max-close/Arrow-collapse-icon.png"));
    }
}

void MainWindow::quitProgram()
{
    ui_settings->setValue("mainwindow_size", this->size());
    ui_settings->setValue("mainwindow_state", this->saveState());
    ui_settings->setValue("main_toolbar_pinned", isMainToolBarPinned);

    ui_settings->setValue("splitter_1", ui->splitter_1->saveState());
    ui_settings->setValue("splitter_2", ui->splitter_2->saveState());
    ui_settings->sync();
//    ui_settings->setValue("splitter_3", ui->splitter_3->saveState());

    on = false;
    close();
    exit(1);
}

