#ifndef SELECTCOLORDIALOG_H
#define SELECTCOLORDIALOG_H

#include <QDialog>
#include "Concepts.h"

namespace Ui {
class SelectColorDialog;
}

class SelectColorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SelectColorDialog(QWidget *parent = 0);
    ~SelectColorDialog();

    SSL::Color getOurColor();
    SSL::Side getOurSide();
    void setStatusText(QString status);
    
private:
    Ui::SelectColorDialog *ui;
};

#endif // SELECTCOLORDIALOG_H
