#ifndef DESIGNDIALOG_H
#define DESIGNDIALOG_H

#include <QDialog>
#include "Ctrls/graphview.h"

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

private slots:
    void on_btnBack_clicked();
    virtual void reject();

    void on_btnSave1_clicked();
    void on_txtH_returnPressed();
    void on_txtW_returnPressed();
    void on_btnReset_clicked();
    void on_btnSave2_clicked();
    void on_loadBtn_clicked();
};

#endif // DESIGNDIALOG_H
