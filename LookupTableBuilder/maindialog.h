#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

namespace Ui {
    class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

private:
    Ui::MainDialog *ui;

private slots:
    void on_input_btn_clicked();
    void on_output_btn_clicked();
    void on_exit_btn_clicked();
    void on_child_rejected();
};

#endif // MAINDIALOG_H
