#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class FieldView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit FieldView(QWidget *parent = 0);
    
signals:
    
public slots:

private slots:
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QPointF mouseLastPosition;
    QTransform mTransform;

    
};

#endif // FIELDVIEW_H
