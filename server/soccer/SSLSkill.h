/*
 * File:   SSLSkill.h
 * Author: mahdi
 *
 * Created on February 13, 2014, 1:06 PM
 */

#ifndef _SSLSKILL_H
#define	_SSLSKILL_H

#include "general.h"
#include "iostream"

class SSLAgent;
class Vector2D;
class Vector3D;

class SSLWorldModel;
class SSLAnalyzer;
class SSLGame;

class SSLSkill {
    
public:
    SSLSkill() { }

    static void halt(SSLAgent* agent);

    static void goToPoint(SSLAgent* agent, Vector3D target, const Vector3D &tolerance);

    static void goToPointWithPlanner(SSLAgent *agent, const Vector3D &target,
                                     const Vector3D &tolerance,
                                     bool considerPenaltyArea = true,
                                     float ball_obs_radius = BALL_RADIUS,
                                     float robot_obs_radius = ROBOT_RADIUS);

    // ************************** Kick Skill *******************************
    static void goAndKick(SSLAgent* agent, Vector2D kick_target, double kickStrenghtNormal = 1);

    static void goAndChip(SSLAgent* agent, double chipStrenghtNormal = 1);

//    static void goBehindBall(SSLAgent* agent, SSLBall* ball);
//    static void blockOpponent(SSLAgent* agent, SSLRobot* opponent);

//    void goToPointKickForBlock(SSLRobot*);
//    void forcKick(SSLRobot*);
//    void forceStop(SSLRobot*);
//    void stopCommands(SSLRobot*); 
    
private:
    static Vector3D calcSpeed(const Vector3D &current, const Vector3D &target);
    static void controlSpeed(SSLAgent* agent, const Vector3D &speed, bool use_controller);

};

#endif	/* _SSLSKILL_H */
