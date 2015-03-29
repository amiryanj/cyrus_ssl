/*
 * File:   sslskill.h
 * Author: mahdi Aali
 *
 * Created on February 13, 2014, 1:06 PM
 */

#ifndef _SSLSKILL_H
#define	_SSLSKILL_H

#include "general.h"
#include "iostream"

#include "../planner/planning/goalstate.h"
#include "../planner/planning/planningproblem.h"
#include "../controller/pidcontroller.h"

class SSLAgent;
class Vector2D;
class Vector3D;

class SSLWorldModel;
class SSLAnalyzer;
class SSLGame;

class SSLSkill {
    
    friend class SSLAgent;
    friend class GUIHandler;
public:
    SSLSkill(SSLAgent* parent);

    void halt();

    void goToPoint(Vector3D target, const Vector3D &tolerance);
    void goToPoint(Vector3D target);
    void goToPoint(Vector2D target, const Vector2D &tolerance);
    void goToPoint(Vector2D target);

    void goToPointWithPlanner( const Vector3D &target,
                               const Vector3D &tolerance,
                               bool considerPenaltyArea = true,
                               float ball_obs_radius = BALL_RADIUS,
                               float robot_obs_radius = ROBOT_RADIUS);

    // ************************** Kick Skill *******************************
    void goAndKick(Vector2D kick_target, double kickStrenghtNormal = 1);

    void goAndChip(double chipStrenghtNormal = 1);

    void goBehindBall(Vector2D ball_position);


//    static void blockOpponent(SSLAgent* agent, SSLRobot* opponent);

//    void goToPointKickForBlock(SSLRobot*);
//    void forcKick(SSLRobot*);
//    void forceStop(SSLRobot*);
//    void stopCommands(SSLRobot*); 
    
    void updateObstacles();
private:
    void move(const Vector3D &current_pos, const Vector3D &target_pos, const Vector3D &tolerance);
    void controlSpeed(const Vector3D &speed, bool use_controller);

    SSLAgent* owner_agent;
    Vector3D Position();
    std::string name;
    Vector3D target;

    PlanningProblem planner;
    PIDController controller;

    Vector3D desiredGlobalSpeed;
    Vector3D appliedGlobalSpeed;

    Obstacle* ballObstacle;
    ObstacleSet allRobotsObstacles;
    ObstacleSet penaltyAreaObstacles;

    Vector3D defaultTolerance;


};

#endif	/* _SSLSKILL_H */
