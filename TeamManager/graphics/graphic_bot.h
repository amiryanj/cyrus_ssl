#ifndef GRAPHIC_BOT_H
#define GRAPHIC_BOT_H
#include <QGraphicsItem>
#include <QImage>

class RobotGraphicsItem : public QGraphicsItem
{

public:
    enum Mode{RobotGraphicMode, RobotTargetGraphicMode, BallGraphicMode,
                      NumberGraphicMode, fieldGridGraphicMode, type6,IdGraphic,Time,Half,CurrentResult};

    bool isInvisible;

    void setNearest(bool nearest);
    void setTotalNearest(bool nearest);
    void setCanKick(bool can_kick);

    QImage image;
    RobotGraphicsItem(Qt::GlobalColor color, int id);
    //for robot and target
//    RobotGraphicsItem(Mode itsMode, int itsID , SSL::Color itsColor, int itsRadius=90);
    //for ball, grids and vectors
    RobotGraphicsItem(Mode mode, int itsDimension = 22);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    QPainterPath shape() const
    {
        QPainterPath path;
        path.addEllipse(boundingRect());
        return path;
    }

private:
    Qt::GlobalColor myColor;
    Mode myMode;
    int  myID;
    int myRadius;
    bool isNearest;
    bool IsTotalNearest;
    bool canKick;
};

#endif // GRAPHIC_BOT_H
