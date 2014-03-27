#ifndef PLAYSTARTER_H
#define PLAYSTARTER_H

#include "sslrole.h"
#include "../SSLSkill.h"

class PlayStarter : public SSLRole
{

public:

    enum KickType { e_Undefined = 0, e_KickOff, e_Penalty, e_Direct, e_Indirect };
    PlayStarter();

    void run();

    Vector3D getBestPosition() const;
    void setBestPosition(const Vector3D &value);

    Vector2D expectedPosition();

    KickType m_kickType;

private:
    Vector3D m_bestPosition;
//    Vector2D opponentPenaltyPoint();
//    Vector2D opponentGoalCenter();
//    Vector3D behindPointPosition(Vector2D point, Vector2D target);

};

#endif // PLAYSTARTER_H
