#ifndef DESIGNDIALOG_H
#define DESIGNDIALOG_H

#include <QDialog>
#include "Ctrls/graphview.h"
#include "../Controller/filecontroller.h"

namespace Ui {
    class DesignDialog;
}

class DesignDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DesignDialog(QWidget *parent = 0);
    ~DesignDialog();

private:
    Ui::DesignDialog *ui;
    QWidget* parentW;

    GraphView* graphView;
    QString fileName;

    QString currentFolder;

private slots:
    void save();
    void reject();

    void on_txtH_returnPressed();
    void on_txtW_returnPressed();
    void on_openBtn_clicked();
    void on_saveButton_clicked();
    void on_saveAsBtn_clicked();
    void on_quitBtn_clicked();
    void on_resetBtn_clicked();
};

#endif // DESIGNDIALOG_H
