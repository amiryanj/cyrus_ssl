#ifndef SSLBALL_H
#define SSLBALL_H

#include "SSLObject.h"

enum {BALL_NOT_STOPPED=0, BALL_STOPPED =1};

class SSLBall : public SSLObject<Vector2D>
{
public:
    SSLBall* mainBall();
    SSLBall();

//    void setFilteredSpeed(const Vector2D & speed);
//    Vector2D getFilteredSpeed() const;

    bool isStopped() const;
    void setStopped(bool stopped = true);

private:
    Vector2D m_filteredSpeed;
    bool m_isStopped;
};

#endif // SSLBALL_H
