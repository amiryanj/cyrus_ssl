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

    static void goToPoint(SSLAgent* agent, Vector3D target, Vector3D tolerance);

    static void goToPointWithPlanner(SSLAgent *agent, Vector3D target, Vector3D tolerance,
                                     bool considerPenaltyArea = true,
                                     float ball_ob_radius = BALL_RADIUS,
                                     float robot_ob_radius = ROBOT_RADIUS);

    static void goAndKick(SSLAgent* agent, double kickStrenghtNormal);

    static void goAndChip(SSLAgent* agent, double chipStrenghtNormal = 1);

//    static void goBehindBall(SSLAgent* agent, SSLBall* ball);
//    static void blockOpponent(SSLAgent* agent, SSLRobot* opponent);

//    void goToPointKickForBlock(SSLRobot*);
//    void forcKick(SSLRobot*);
//    void forceStop(SSLRobot*);
//    void stopCommands(SSLRobot*);

    static Vector2D opponentPenaltyPoint();
    static Vector2D opponentGoalCenter();
    static Vector2D ourGoalCenter();
    static Vector3D KickStylePosition(Vector2D point, Vector2D kickTarget);
    
private:
    static void goTowards(SSLAgent* agent, Vector3D target);
    static void buildAndSendPacket(int id, Vector3D &vel, float kickSpeed = 0);
    static void printRobotAppliedSpeed(SSLAgent* agent, std::ostream& stream);

};

#endif	/* _SSLSKILL_H */
