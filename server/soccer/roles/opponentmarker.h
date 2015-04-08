#ifndef _OPPONENTMARKER_H
#define _OPPONENTMARKER_H

#include "../sslrole.h"
#include "../../definition/SSLRobot.h"
#include "../sslskill.h"

class OpponentMarker : public SSLRole
{

public:
    OpponentMarker(int index_);

    void run();

    Vector3D expectedPosition();

    int m_index;

private:
};

#endif //_ OPPONENTMARKER_H
