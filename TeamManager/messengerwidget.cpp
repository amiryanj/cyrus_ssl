#include "messengerwidget.h"
#include <QVBoxLayout>
#include <map>
#include <vector>
#include <QDebug>

MessengerWidget::MessengerWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout * my_layout = new QVBoxLayout;
    text=new QTextEdit();
    text->setReadOnly(true);
    combo = new QComboBox();
    combo->addItem("All");
    connect(combo,SIGNAL(currentIndexChanged(QString)),this,SLOT(comboChange(QString)));
    my_layout->addWidget(combo);
    my_layout->addWidget(text);
    setLayout(my_layout);
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(printText()));
    timer->start(100);



}

void MessengerWidget::printText()
{
    if(text->document()->lineCount() > 6000)
        text->clear();
    if(buffer.size() >0)
        text->append(buffer);
    buffer.clear();
}

void MessengerWidget::newMessage(const char *msg, QString category)
{
    if(messages.find(category) == messages.end() )
    {
        combo->addItem(category);
    }
    messages[category].push_back(msg);
    allMessages.push_back(msg);
    if(combo->currentText() == category || combo->currentText() == "All")
    {
        buffer.append(msg);
        buffer.append('\n');

    }
   //  qDebug()<<"CHange"<<QThread::currentThreadId();
}

void MessengerWidget::comboChange(QString category)
{
    text->clear();
    buffer.clear();
    std::vector<const char *> * vec;
    vec=&messages[category];
    if(category == "All")
        vec=&allMessages;
    else
        vec=&messages[category];

    for(std::vector<const char *>::iterator it = vec->end()-std::min(200,(int)vec->size()); it != vec->end() ; it++)
    {
        buffer.append(*it);
        buffer.append('\n');
    }
}
