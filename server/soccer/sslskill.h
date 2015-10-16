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
#include "../paramater-manager/lookuptableloader.h"
#include "../vartypes/VarTypesBase.h"


class SSLAgent;
class Vector2D;
class Vector3D;

class SSLWorldModel;
class SSLAnalyzer;
class SSLGame;

using namespace VarTypes;

class SSLSkill {
    
    friend class SSLAgent;
    friend class GUIHandler;
public:
    enum MoveType{eAccurateMove, eSlowMove, eFastMove, eAutoMove};

    SSLSkill(SSLAgent* parent);

    void halt();

    void goToPoint(Vector3D target, const Vector3D &tolerance, MoveType move_type = eAutoMove);
    void goToPoint(Vector3D target, MoveType move_type = eAutoMove);
    void goToPoint(Vector2D target, const Vector2D &tolerance, MoveType move_type = eAutoMove);
    void goToPoint(Vector2D target, MoveType move_type = eAutoMove);

    void goGlobalSpeed(Vector3D &inp, bool use_controller = true);
    void goLocalSpeed(Vector3D &inp, bool use_controller = true);

    void goToSubGoal(const Vector3D &target, const Vector3D &tolerance, MoveType move_type);

    void gotoPointWithLookupTable(Vector3D target);

    void goToPointWithPlanner( const Vector3D &target,
                               const Vector3D &tolerance,
                               bool considerPenaltyArea = true,
                               float ball_obs_radius = BALL_RADIUS,
                               float robot_obs_radius = ROBOT_RADIUS,
                               MoveType move_type = eAutoMove);

    // ************************** Kick Skill *******************************
    void goAndKick(const Vector2D kick_point, const Vector2D kick_target, float kickStrenghtNormal = 1);

    void goAndChip(double chipStrenghtNormal = 1);

    void goBehindBall(Vector2D ball_position);


//    static void blockOpponent(SSLAgent* agent, SSLRobot* opponent);

//    void goToPointKickForBlock(SSLRobot*);
//    void forcKick(SSLRobot*);
//    void forceStop(SSLRobot*);
//    void stopCommands(SSLRobot*); 
    
    void updateObstacles();
    static double computeVelocityStrenghtbyDistance(double dist , double max_speed);
    static Vector3D defaultTolerance;
    static Vector3D accurateTolerance;

//    void rotateByDegree(float current_orien_deg, float rotation_deg, float omega);
    void rotate(float omega);

private:
    void accurateMove(const Vector3D &current_pos, const Vector3D &target_pos, const Vector3D &tolerance);
    void slowMove(const Vector3D &current_pos, const Vector3D &target_pos, const Vector3D &tolerance , double speed_coeff = 0.0);
    void fastMove(const Vector3D &current_pos, const Vector3D &target_pos, const Vector3D &tolerance);


    void controlSpeed(const Vector3D &desired_global_speed, bool use_controller, bool global_vel = true);
    void initializePlanner();

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

    double rotate_call_deadline_time_ms;
    double avoid_rotate_deadline_time_ms;

    bool kickTheBall;

    LookupTableLoader lookup_tabler;



};

#endif	/* _SSLSKILL_H */
