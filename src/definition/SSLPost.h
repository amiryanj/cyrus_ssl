#ifndef SSLPOST_H
#define SSLPOST_H

#include "general.h"

enum SoccerPost{NullPost = 0, MAP, GK, CB, RB, LB, SW, DMF, CMF, RMF, LMF, AMF, RWF, LWF, SS, CF};
// **** MAP = Most Active Player ****

class SSLPost
{
public:
    SSLPost(SoccerPost p = NullPost);

    SoccerPost postName;
    Vector2D centerOfAction;




};

#endif // SSLPOST_H
