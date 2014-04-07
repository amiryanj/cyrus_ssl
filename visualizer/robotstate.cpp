#include "robotstate.h"
#include "iostream"

using namespace std;

RobotState::RobotState()
{
}

RobotState::RobotState(SSL::Color c, int id)
{
    this->color = c;
    this->ID = id;
}

void RobotState::print()
{
    cout << "Robot State: Color: " << color << " , id: " << ID << endl;
    cout << "Position [X: " << position.X() << " , Y: " << position.Y() << " , orien: " << position.Teta() << endl;
    cout << "Velocity [X: " << velocity.X() << " , Y: " << velocity.Y() << " , orien: " << velocity.Teta() << endl;
}

QString RobotState::colorIDString()
{
    return QString((this->color==SSL::Blue)? "Blue%1":"Yellow%1").arg(ID);
}

BallState::BallState(int id)
{
    this->ID = id;
}

void BallState::print()
{
    cout << "Ball State: id: " << ID << endl;
    cout << "Position [X: " << position.X() << " , Y: " << position.Y() << endl;
    cout << "Velocity [X: " << velocity.X() << " , Y: " << velocity.Y() << endl;
}
