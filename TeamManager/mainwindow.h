#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "watchfieldgraphics.h"

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
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initGUI();
    void setupGUIConnections();
    
private:
    Ui::MainWindow *ui;
    WatchFieldGraphics *watchField;

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