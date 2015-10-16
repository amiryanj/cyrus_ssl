#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "watchfieldgraphics.h"
#include "plot-manager/plotmanagerwidget.h"
#include "messengerwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum MainTab {e_TabWatch, e_TabCommand, e_TabDesign, e_TabAI
                    , e_TabHardware}  currentTab;

    enum VisionSource {e_SourceSSLVision, e_SourceGRSim, e_SourceCyrus
                        , e_SourceLogFile}  chosenVisionSource;

    explicit MainWindow(QWidget *parent = 0);
    static MainWindow* instance;

    Ui::MainWindow *ui;
    QSettings *ui_settings;
    bool isMainToolBarPinned;

public:
    static MainWindow* getInstance();
    ~MainWindow();
    void closeEvent(QCloseEvent* e);
    void initGUI();
    void setupGUIConnections();
    
    WatchFieldGraphics *watchField;
    PlotManagerWidget *PMW;
    MessengerWidget * MSG;

    static bool turn_off;
    static bool idle_server;
    static bool idle_vision;

private slots:
    void handleChoosingVisionSource();
    void setEnabledLogControlPanel(bool enabled_);

    void setEnabledShowItemButtons(bool enabled_);
    void handleChangingMainTab();
    void setCurrentTabTo(MainTab tab_);

    void handlePinMainToolBarBtn();

    void quitProgram();

    void on_actionIdle_Server_toggled(bool arg1);
    void on_actionIdle_Vision_toggled(bool arg1);
};

#endif // MAINWINDOW_H
