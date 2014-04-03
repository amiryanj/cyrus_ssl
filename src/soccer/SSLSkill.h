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

    static void goToPoint(SSLAgent* agent, const Vector3D &target, const Vector3D &tolerance);

    static void goToPointWithPlanner(SSLAgent *agent, const Vector3D &target, const Vector3D &tolerance,
                                     bool considerPenaltyArea = true,
                                     float ball_ob_radius = BALL_RADIUS,
                                     float robot_ob_radius = ROBOT_RADIUS);

    static void goAndKick(SSLAgent* agent, double kickStrenghtNormal = 1);

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
    static Vector3D ourMidfieldUpPosition();
    static Vector3D ourMidfieldDownPosition();
    static Vector3D opponentMidfieldUpPosition();
    static Vector3D opponentMidfieldDownPosition();
    static Vector3D KickStylePosition(const Vector2D &kick_point, const Vector2D &kickTarget, float dist = 100);
    static Vector3D DefenseStylePosition(const Vector2D &risky_point, const Vector2D &defense_point,
                                         float dist = 2 * ROBOT_RADIUS);
    
private:
    static void buildAndSendPacket(int id, Vector3D &vel, float kickSpeed = 0);
    static void printRobotAppliedSpeed(SSLAgent* agent, std::ostream& stream);
    static void controlSpeed(SSLAgent* agent, const Vector3D &speed);

};

#endif	/* _SSLSKILL_H */
