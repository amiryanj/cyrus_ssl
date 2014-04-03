#ifndef SSLBALL_H
#define SSLBALL_H

#include "SSLObject.h"

class SSLBall : public SSLObject<Vector2D>
{
public:
    SSLBall();

    void setFilteredSpeed(const Vector2D & speed);
    Vector2D getFilteredSpeed() const;

private:
    Vector2D m_filteredSpeed;
};

#endif // SSLBALL_H
