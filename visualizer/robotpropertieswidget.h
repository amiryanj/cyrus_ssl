#ifndef ROBOTPROPERTIESWIDGET_H
#define ROBOTPROPERTIESWIDGET_H

#include <QWidget>

namespace Ui {
class RobotPropertiesWidget;
}

class RobotPropertiesWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit RobotPropertiesWidget(bool isOurs = true, QWidget *parent = 0);
    ~RobotPropertiesWidget();
    
private:
    Ui::RobotPropertiesWidget *ui;
};

#endif // ROBOTPROPERTIESWIDGET_H
