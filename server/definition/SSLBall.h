#ifndef SSLBALL_H
#define SSLBALL_H

#include "SSLObject.h"
#include <cmath>

enum {BALL_NOT_STOPPED=0, BALL_STOPPED =1};

struct SSLBallState {
                                /// @variable unit
    short    camera_id;
    double   timeStamp_second;  // second
    Vector2D position;          // mili meter
    Vector2D displacement;      // mili meter
    Vector2D velocity;          // mili meter per second
    Vector2D acceleration;      // mili meter per second^2
    float turnInDegree() const {return acceleration.arctan() * 180.0/M_PI;}
};

class SSLBall : public SSLObject<Vector2D>
{
public:
    SSLBall()  {
        m_radius = 22.0f;
        m_stopped = true;
    }

    void setStopped(bool stopped)  {
        m_stopped = stopped;
    }

    bool isStopped() const  {
        return m_stopped;
    }

private:
    Vector2D m_filteredSpeed;
    bool m_stopped;
};

#endif // SSLBALL_H
