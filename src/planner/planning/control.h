#ifndef CONTROL_H
#define CONTROL_H

class Control
{
public:
    Control();

    double Vx;
    double Vy;
    double Wz;

    void operator =(Control& other);

};

#endif // CONTROL_H
