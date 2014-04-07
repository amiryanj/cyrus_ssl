#ifndef SELECTPLOTDIALOG_H
#define SELECTPLOTDIALOG_H

#include <QDialog>

namespace Ui {
class SelectPlotDialog;
}

class SelectPlotDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SelectPlotDialog(QWidget *parent = 0);
    ~SelectPlotDialog();

    bool is_x_selected();
    bool is_y_selected();
    bool is_mag_selected();
    bool is_teta_selected();
    
private:
    Ui::SelectPlotDialog *ui;
};

#endif // SELECTPLOTDIALOG_H
