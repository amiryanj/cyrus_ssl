/*
 * File:   SSLSkill.h
 * Author: mahdi
 *
 * Created on February 13, 2014, 1:06 PM
 */

#ifndef SSLSKILL_H
#define	SSLSKILL_H

#include <iostream>

#include "../definition/SSLRobot.h"
#include "../definition/sslagent.h"
#include "../definition/SSLBall.h"


class SSLSkill {
    
public:
    SSLSkill();
    
    static void goToPoint(SSLAgent* agent, Vector2D target);

    static void goBehindBall(SSLAgent* agent, SSLBall* ball);

    static void kick(SSLAgent* agent);

    static void blockOpponent(SSLAgent* agent, SSLRobot* opponent);

//    void goToPointKickForBlock(SSLRobot*);
//    void forcKick(SSLRobot*);
//    void forcKick(SSLRobot*, long duration);
//    void forceStop(SSLRobot*);
//    void stopCommands(SSLRobot*);
    
private:

};

#endif	/* SSLSKILL_H */
