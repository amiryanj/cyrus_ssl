/* 
 * File:   AreaPlayMaker.h
 * Author: mahdi
 *
 * Created on February 19, 2014, 1:03 PM
 */

#ifndef PLAYMAKER_H
#define	PLAYMAKER_H

#include "sslrole.h"

class PlayMakerRole : public SSLRole
{

public:
    PlayMakerRole(SSLAgent* agent);
    
    void run();
private:

};

#endif	/* AREAPLAYMAKER_H */

