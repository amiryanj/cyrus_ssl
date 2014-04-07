#include "graphic_num.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

NumberGraphicsItem::NumberGraphicsItem(int num_)
{
    number = num_;
}

void NumberGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->setPen((this->myColor==Qt::blue)? QColor(Qt::white):QColor(Qt::black));
        painter->setFont(QFont("Calibri",80, 0.8));
        QString numStr;
        numStr.setNum(this->number);
        (this->myColor==Qt::blue)? (painter->drawText(-20,60,numStr)) : (painter->drawText(-35,40,numStr));
        if(!myText.isEmpty())
            painter->drawText(-20,-50, myText);
        this->setRotation(-this->parentItem()->rotation());
}

QRectF NumberGraphicsItem::boundingRect() const
{
    return QRectF(-5,-5, 2*5,2*5);
}

void NumberGraphicsItem::setText(QString text_)
{
    myText = text_;
}
