#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "watchfieldgraphics.h"
#include "plot-manager/plotmanagerwidget.h"

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

    bool isMainToolBarPinned;
    
    Ui::MainWindow *ui;
    explicit MainWindow(QWidget *parent = 0);
    static MainWindow* instance;

public:
    static MainWindow* getInstance();
    ~MainWindow();

    void initGUI();
    void setupGUIConnections();
    
    WatchFieldGraphics *watchField;
    PlotManagerWidget *PMW;
    static bool on;

private slots:
    void handleChoosingVisionSource();
    void setEnabledLogControlPanel(bool enabled_);

    void setEnabledShowItemButtons(bool enabled_);
    void handleChangingMainTab();
    void setCurrentTabTo(MainTab tab_);

    void handlePinMainToolBarBtn();

    void quitProgram();

};

#endif // MAINWINDOW_H
