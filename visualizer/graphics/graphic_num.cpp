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
    painter->setPen((myColor == Qt::blue)? QColor(255,255,230) : QColor(0,70,50));
    painter->setFont(QFont("Ubuntu", 80, 0.8));
    QString numStr;
    numStr.setNum(this->number);
    ( this->number < 10 )? (painter->drawText(-30,60,numStr)) : (painter->drawText(-70, 50,numStr));
    if(!myText.isEmpty())
    {
        painter->setPen((myColor == Qt::blue)? Qt::black : Qt::black);
        painter->drawText(-20,-50, myText);
    }
//    this->setRotation(-this->parentItem()->rotation());
}

QRectF NumberGraphicsItem::boundingRect() const
{
    return QRectF(-70,-50, 140, 100);
}

void NumberGraphicsItem::setText(QString text_)
{
    myText = text_;
}

void NumberGraphicsItem::setColor(Qt::GlobalColor color)
{
    myColor = color;

}
