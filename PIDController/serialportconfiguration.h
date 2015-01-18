#ifndef SERIALPORTCONFIGURATION_H
#define SERIALPORTCONFIGURATION_H

#include <QDialog>

namespace Ui {
class SerialPortConfiguration;
}

class SerialPortConfiguration : public QDialog
{
    Q_OBJECT

public:
    explicit SerialPortConfiguration(QWidget *parent = 0);
    ~SerialPortConfiguration();

private:
    Ui::SerialPortConfiguration *ui;
};

#endif // SERIALPORTCONFIGURATION_H
