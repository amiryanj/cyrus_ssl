#ifndef MESSENGERWIDGET_H
#define MESSENGERWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QComboBox>
#include <map>
#include <vector>
#include <QThread>
#include <QTimer>
class MessengerWidget : public QWidget
{
    Q_OBJECT
    QTextEdit * text;
    QComboBox * combo;
    std::map<QString, std::vector<const char *> > messages;
    std::vector<const char *> allMessages;
    QTimer* timer ;
    QString buffer;
public:
    explicit MessengerWidget(QWidget *parent = 0);

signals:
private slots:
    void printText();
public slots:
    void newMessage(const char * msg , QString category);
    void comboChange(QString category);

};

#endif // MESSENGERWIDGET_H
