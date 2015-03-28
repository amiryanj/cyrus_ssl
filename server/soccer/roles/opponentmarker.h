#ifndef _OPPONENTMARKER_H
#define _OPPONENTMARKER_H

#include "../sslrole.h"
#include "../../definition/SSLRobot.h"
#include "../sslskill.h"

class OpponentMarker : public SSLRole
{

public:
    OpponentMarker();

    void run();

    Vector3D expectedPosition();

private:
};

#endif //_ OPPONENTMARKER_H
