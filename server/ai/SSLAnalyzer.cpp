#include "SSLAnalyzer.h"

#include "SSLGame.h"
#include "SSLWorldModel.h"
#include "../definition/SSLRobot.h"
#include "../definition/SSLBall.h"
#include "../../common/math/linesegment.h"
#include "../soccer/sslgamepositions.h"

#include <utility>
#include <cmath>

#define defnum 0.1
#define goalposition 3025
#define goalLeftPost 1675
#define goalRightPost 2375
#define robotObstacle 100
#define BALL_FRICTION_COEFF  4.0
#define BALL_SPEED_THRESHOLD_FOR_CROSS 400.0

#define POSSESSION_THRESHOLD 0.03

#define EPS 1e-6


int cmp(float a, float b) {
    if (a < b - EPS)
        return -1;
    if (a > b + EPS)
        return 1;
    return 0;
}

SSLAnalyzer* SSLAnalyzer::analyzer_instance = NULL;

SSLAnalyzer::SSLAnalyzer()
{
    m_game_running = false;

//    for(int tm = 0; tm < 2; tm++)
//        for(int j=0; j < MAX_ID_NUM; j++)
//        {
//            this->distToBall[tm][j] = new RobotDistTo(world->team[tm]->robot[j], world->ball);
//        }
}

SSLAnalyzer* SSLAnalyzer::getInstance()
{
    if(analyzer_instance == NULL)
        analyzer_instance = new SSLAnalyzer();
    return analyzer_instance;
}


void SSLAnalyzer::check()
{
    initialize_caches();
    try {

        if(m_game_running == true) {
            if(world->m_refereeState == SSLReferee::Stop || world->m_refereeState == SSLReferee::Halt) {
                m_game_running = false;
                ball_move_counter = 0;

            }
        }
        else // check if game gets running
        {
//            ball_stop_position = world->mainBall()->Position();
            if(world->m_refereeState == SSLReferee::ForceStart)
                m_game_running = true;
            else if((isOurDirectKick() ||  isOpponentDirectKick() ||
                    isOurIndirectKick() || isOpponentIndirectKick() ||
                    isOurKickOffKick() || isOpponentKickOffKick() ||
                    isOurPenaltyKick() || isOpponentPenaltyKick() ))
            {
                if((world->mainBall()->Speed().lenght() > 80)) { //  milimeter per sec)
                    ball_move_counter ++;
                }
                if(ball_move_counter > 20)
                    m_game_running = true;
            }
        }
    }
    catch(const char* mes) {
        cerr << "Exception SSLAnalizer : " << mes <<endl;
    }
        //            vector<SSLRobot* > nears = nearestRobotToBall(world->all_inFields());
        //            if(nears.empty())
        //                return;
        //            SSLRobot* near = nears[0];
        //            double diff2Ball = (near->Position().to2D() - world->mainBall()->Position()).lenght();
        //            if(diff2Ball < (BALL_RADIUS + ROBOT_RADIUS))


//        if(game->ourTeam()->inFields().empty())
//            throw "The team infield attribute is empty.";
//        vector<SSLRobot *> defenders  = blockersFromPoint(world->mainBall()->Position());
//        if(defenders.empty())
//            throw "cannot find any defenders";
//        for (int i = 0; i < defenders.size(); i++)
//            cout << "defender " << i << " is : " << defenders[i]->id <<  " from team " << defenders[i]->color << endl;
//        vector<pair<float, float> > openAngle = openAngleToGoal(world->mainBall()->Position());
//        cout << "Angles:" << endl;
//        for (int i = 0; i < openAngle.size(); i++)
//            cout << openAngle[i].first << " " << openAngle[i].second << endl;


}

double SSLAnalyzer::distanceFromBall(const Vector2D &point)
{
    if(world->mainBall() != NULL)
        return (world->mainBall()->Position() - point).lenght();
    else
        return -1;
}
double SSLAnalyzer::distanceFromBall(const SSLRobot *robot)
{
    if(world->mainBall() != NULL && robot != NULL) {
        uint hashID = _getHashID(robot);
        if (f_distance_robot_ball[hashID] == 0) {
            f_distance_robot_ball[hashID] = 1;
            return c_distance_robot_ball[hashID] =
                    (world->mainBall()->Position() - robot->Position().to2D()).lenght();
        }
        return c_distance_robot_ball[hashID];
    }
    else
        return -1;
}

double SSLAnalyzer::distanceFromRobotToPoint(const Vector2D &point, const SSLRobot *robot)
{
    if(robot != NULL)
        return (robot->Position().to2D() - point).lenght();
    else
        return -1;
}
double SSLAnalyzer::distanceFromRobotToRobot(const SSLRobot* robot1,const SSLRobot* robot2)
{
    if(robot1 != NULL && robot2 != NULL) {
        uint hashID1 = _getHashID(robot1), hashID2 = _getHashID(robot2);
        if (f_distance_robot_robot[hashID1][hashID2] == 0) {
            f_distance_robot_robot[hashID1][hashID2] = 1;
            return c_distance_robot_robot[hashID1][hashID2] =
                    (robot1->Position().to2D() - robot2->Position().to2D()).lenght();
        }
        return c_distance_robot_robot[hashID1][hashID2];
    }
    else
        return -1;
}

SSLRobot *SSLAnalyzer::whichRobotCanKick()
{
    if (f_whichRobotCanKick == 0) {
        f_whichRobotCanKick = 1;
        vector<SSLRobot* > robots = world->getInFieldRobots();

        for(uint i = 0 ; i < robots.size() ; i ++)
        {
            if(distanceFromBall(robots[i]) < robotObstacle && distanceFromBall(robots[i]) != -1)
            {
                Vector2D dis = world->mainBall()->Position()-robots[i]->Position().to2D();
                double ang = dis.arctan();
                if(fabs(robots[i]->orien() - ang) < (M_PI / 6.0 ) )
                {
                    return c_whichRobotCanKick = robots[i];
                }
                else
                    continue;
            }
        }
        return c_whichRobotCanKick = NULL;
    }
    return c_whichRobotCanKick;
}

bool SSLAnalyzer::canKick(SSLRobot *robot)
{
    uint hashID = _getHashID(robot);
    if (f_canKick[hashID] == 0) {
        f_canKick[hashID] = 1;
        if(distanceFromBall(robot) < ((BALL_RADIUS + ROBOT_RADIUS) * 1.18)
                && ((robot->Position().to2D() - world->mainBall()->Position()).Y() < 30))
        {
            Vector2D dis = world->mainBall()->Position() - robot->Position().to2D();
            double ang = dis.arctan();
            if(fabs(robot->orien() - ang) < (M_PI / 7.0 ) )
                return c_canKick[hashID] = true;
        }
        return c_canKick[hashID] = false;
    }
    return c_canKick[hashID];
}


SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotIntersectBall(uint index)
{    
    return nearestRobotIntersectBall(world->getInFieldRobots(), index);
}

SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotIntersectBall(Color teamColor, uint index)
{
    return nearestRobotIntersectBall(world->getTeam(teamColor)->getInFieldRobots(), index);
}

SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotIntersectBall(const vector<SSLRobot *> &robots, uint index)
{
    vector<RobotIntersectTime> timeForEachRobot;
    try {
        if(index >= robots.size()) {
            throw "Nearest Robot Could not find";
        }
        for(uint i = 0 ; i < robots.size(); i++ )
        {
            SSLAnalyzer::RobotIntersectTime res = whenWhereCanRobotCatchTheBall(robots[i]);
            timeForEachRobot.push_back(res);
        }
        sort(timeForEachRobot.begin(), timeForEachRobot.end());
        return timeForEachRobot[index];
    }
    catch (const char* mes) {
        //cerr << "Warning: " << "SSLAnalyzer" << mes << endl;
        return RobotIntersectTime();
    }
}

SSLRobot *SSLAnalyzer::nearestToBall(const vector<SSLRobot *> robots, uint index)
{
    RobotIntersectTime intersect_(nearestRobotIntersectBall(robots, index));
    if(intersect_.isValid())  {
        return intersect_.m_robot;
    }
    return NULL;
}

//----------------------------------------------------------------------------------------------
// TODO : Nariman*****************************************************************************
SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToPoint(const Vector2D &point, uint index)
{
    return nearestRobotToPoint(world->getInFieldRobots(), point, index);
}

SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToPoint(Color teamColor, const Vector2D &point, uint index)
{
    return nearestRobotToPoint(world->getTeam(teamColor)->getInFieldRobots(), point, index);
}

SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToPoint(const vector<SSLRobot *> &robots, const Vector2D &point, uint index)
{
    if(index >= robots.size())
        return RobotIntersectTime();
    vector<RobotIntersectTime> robotIntersectPoints;
    robotIntersectPoints.reserve(robots.size());
    for(uint i = 0 ; i < robots.size() ; i++)
    {
        SSLRobot* robot = robots[i];
        assert(robot != NULL);
        SSLAnalyzer::RobotIntersectTime res;
        res.m_time = distanceFromRobotToPoint(point, robot) / robot->physic.max_lin_vel_mmps; // whenWhereCanRobotCatchTheBall(robots[i]);
        res.m_robot = robot;
        res.m_position = point;
        robotIntersectPoints.push_back(res);
    }
    sort(robotIntersectPoints.begin(), robotIntersectPoints.end());
    return robotIntersectPoints[index];
}

SSLRobot *SSLAnalyzer::nearestToPoint(const vector<SSLRobot *> &robots, const Vector2D &point, uint index)
{
    RobotIntersectTime intersect_(nearestRobotToPoint(robots, point, index));
    if(intersect_.isValid()) {
        return intersect_.m_robot;
    }
    return NULL;
}
// ------------------------------------------------------------------------------------------
//SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToRobot(const SSLRobot *robot, uint index)
//{

//}
//SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToRobot(SSL::Color teamColor, const SSLRobot *robot, uint index)
//{

//}
//SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToRobot(const vector<SSLRobot *> &robots, const SSLRobot *robot, uint index)
//{

//}

//SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotsToBlockPointOutOfOurPenaltyArea(const Vector2D targetPoint, uint index)
//{

//}

//SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotsToBlockPoint(const Vector2D targetPoint, uint index)
//{

//}

//SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotsToMarkRobot(const SSLRobot * robot, uint index)
//{
//    // nearest robot robot :D
//}

//point opponentBlockerFromPoint
vector<SSLRobot *> SSLAnalyzer::blockersFromPoint(const Vector2D targetPoint)
{
    SSLRobot* hashed[MAX_ID_NUM << 1];
    memset(hashed, 0, sizeof hashed);
    float r = ROBOT_RADIUS - 2.0;
    int repeat = FIELD_GOAL_WIDTH / (2.0*r);
    for(int i = 0  ; i <= repeat; i ++ )
    {
        float y2 = (-FIELD_GOAL_WIDTH/2.0)+i*2.0*r;
        float xDelta = -(game->ourSide())*FIELD_LENGTH/2.0 - targetPoint.X();
        float m = (y2 - targetPoint.Y()) / xDelta;
        float b = m*(-targetPoint.X());
        vector<SSLRobot*> robots = world->getInFieldRobots();
        for(uint j = 0 ; j < robots.size() ; j++)
        {
            SSLRobot* robot = robots[j];
            if (!robot->isInField) continue;
            float rx = robot->Position().X();
            float ry = robot->Position().Y();
            if ((targetPoint.X() < rx && game->ourSide() == -1)
                    || (rx < targetPoint.X() && game->ourSide() == 1)) {
                float delta = -b*b + r*r + m*m*r*r - 2.0*b*m*rx - m*m*rx*rx +
                        2.0*b*ry + 2.0*m*rx*ry - ry*ry;
                 if (delta >= 0.0) {
                    hashed[_getHashID(robot)] = robot;
                }
            }
        }
     }
    vector<SSLRobot *> blockers;
    for (int i = 0; i < 24; i++)
        if (hashed[i] != NULL)
            blockers.push_back(hashed[i]);
    return blockers;
}



pair<float, float> SSLAnalyzer::blockedAngleByARobot(const Vector2D & targetPoint, const SSLRobot *robot) {
    /**
     * returns pair<low angle, high angle> of the blocked view
     */
    float theta = atan2(robot->Position().Y() - targetPoint.Y(), robot->Position().X() - targetPoint.X());
    float distance = (robot->Position().to2D() - targetPoint).lenght();
    float alpha = asin(ROBOT_RADIUS / distance);
    float up = theta + alpha;
    float down = theta - alpha;
    if (game->ourSide() == SSL::Left) {
        return make_pair(down, up);
    }
    else {
        return make_pair(positiveSideAngleInNegativeSide(down*(((down < 0)<<1) -1)),
                positiveSideAngleInNegativeSide(up*(((up < 0)<<1)-1)));
    }
}

float SSLAnalyzer::positiveSideAngleInNegativeSide(float angle) const
{
    const float pi = acos(-1.0);
    return -angle + pi*(((angle>0)<<1)-1);
}

float SSLAnalyzer::negativeSideAngleInPositiveSide(float angle) const
{
    const float pi = acos(-1.0);
    return pi + angle*(((angle < -pi/2.0)<<1)-1);
}

// must be check ......
vector<pair<float,float> > SSLAnalyzer::openAngleToGoal(const Vector2D targetPoint)
{
    vector<SSLRobot *> defenders = blockersFromPoint(targetPoint);
    vector<pair<float, float> > blockedAngles;
    float xDelta = -(game->ourSide())*FIELD_LENGTH/2.0 - targetPoint.X();
    float m1 = ((-FIELD_GOAL_WIDTH/2.0) - targetPoint.Y()) / xDelta;
    float m2 = ((FIELD_GOAL_WIDTH/2.0) - targetPoint.Y()) / xDelta;
    float downAngle = atan(m1);
    float upAngle = atan(m2);
    blockedAngles.push_back(make_pair(downAngle, downAngle));
    for (uint i = 0; i < defenders.size(); i++)
        blockedAngles.push_back(blockedAngleByARobot(targetPoint, defenders[i]));
    blockedAngles.push_back(make_pair(upAngle, upAngle));

    if (game->ourSide() == 1)
        for (int i = 1; i < int(blockedAngles.size()) - 1; i++) {
            blockedAngles[i].first = negativeSideAngleInPositiveSide(blockedAngles[i].first);
            blockedAngles[i].second = negativeSideAngleInPositiveSide(blockedAngles[i].second);
        }

    sort(blockedAngles.begin(), blockedAngles.end());
    vector<pair<float, float> > openAngles;
    uint start, last;
    start = 0;
    while (start < blockedAngles.size()) {
        float limit = blockedAngles[start].second;
        last = start + 1;
        if (last == blockedAngles.size())
            break;
        while (last < blockedAngles.size()) {
            if (blockedAngles[last].first < limit) {
                limit = max(limit, blockedAngles[last].second);
                last++;
            }
            else
                break;
        }
        openAngles.push_back(make_pair(limit, blockedAngles[last].first));
        start = last;
    }
    return openAngles;
}

float SSLAnalyzer::wastedTimeForInertia(SSLRobot *robot, Vector2D target) const
{
    Vector2D diff = target - robot->Position().to2D();
    float cos_theta = cos(diff.arctan() - robot->Speed().to2D().arctan());
    float wastedTime = (robot->physic.max_lin_vel_mmps - robot->Speed().lenght2D()*cos_theta) / robot->physic.max_lin_acc_mmps2;
    return wastedTime;
}

SSLAnalyzer::RobotIntersectTime SSLAnalyzer::whenWhereCanRobotCatchTheBall_imp1(SSLRobot* robot)
{
    if(world->mainBall()->Speed().lenght() < 1000) {
        RobotIntersectTime stopCaseAnswer;
        stopCaseAnswer.m_robot = robot;
        stopCaseAnswer.m_position = world->mainBall()->Position();
        stopCaseAnswer.m_time = distanceFromBall(robot) / robot->physic.max_lin_vel_mmps;
        return stopCaseAnswer;
    }

    Vector2D ball_direction_vector = world->mainBall()->Speed().normalized();

    // multiply it by INFINITY number = field_lenght
    ball_direction_vector *= FIELD_LENGTH;
    Vector2D ball_target = world->mainBall()->Position() + ball_direction_vector;

    LineSegment ball_path_line(world->mainBall()->Position(), ball_target);
    Vector2D nearest_expected_catch_point = ball_path_line.nearestPointFrom(robot->Position().to2D());
    float t_catch = (nearest_expected_catch_point - robot->Position().to2D()).lenght()
                                          / robot->physic.max_lin_vel_mmps;

    float t_arrive_ball = (nearest_expected_catch_point - world->mainBall()->Position()).lenght()
                                          / world->mainBall()->Speed().lenght();

    if( t_catch < t_arrive_ball) {
        RobotIntersectTime canCatchCaseAnswer;
        canCatchCaseAnswer.m_robot = robot;
        canCatchCaseAnswer.m_position = nearest_expected_catch_point;
        canCatchCaseAnswer.m_time = t_arrive_ball;
        return canCatchCaseAnswer;
    }

    if(world->mainBall()->Speed().lenght() > robot->physic.max_lin_vel_mmps) {
        RobotIntersectTime unableToCatchCaseAnswer;
        unableToCatchCaseAnswer.m_robot = robot;
        unableToCatchCaseAnswer.m_time = (FIELD_LENGTH / robot->physic.max_lin_vel_mmps)
            + (world->mainBall()->Position() - robot->Position().to2D()).lenght() / robot->physic.max_lin_vel_mmps;
        unableToCatchCaseAnswer.m_position = Vector2D(INFINITY, INFINITY);
        return unableToCatchCaseAnswer;
    }

    // in the case that robots follows the ball in the same direction
    RobotIntersectTime tryToCatchCaseAnswer;
    tryToCatchCaseAnswer.m_robot = robot;
    // fisrst assume that robo
    float time_get_current_ball_pos = (world->mainBall()->Position() - robot->Position().to2D()).lenght()/robot->physic.max_lin_vel_mmps;
    Vector2D where_is_ball_now = world->mainBall()->Position() + world->mainBall()->Speed() * time_get_current_ball_pos;
    float time_get_ball = fabs(robot->physic.max_lin_vel_mmps - world->mainBall()->Speed().lenght()) /
                                       (where_is_ball_now - world->mainBall()->Position()).lenght();
    tryToCatchCaseAnswer.m_time = time_get_ball + time_get_current_ball_pos;
    tryToCatchCaseAnswer.m_position = world->mainBall()->Position()
                                    + world->mainBall()->Speed() * tryToCatchCaseAnswer.m_time ;
    return tryToCatchCaseAnswer;
}

SSLAnalyzer::RobotIntersectTime SSLAnalyzer::whenWhereCanRobotCatchTheBall(SSLRobot* robot) {
    const SSLBall* ball = world->mainBall();

    if (robot && ball) {
        uint hashID = _getHashID(robot);
        if (f_whenWhereCanCatchTheBall[hashID] == 0) {
            f_whenWhereCanCatchTheBall[hashID] = 1;
            return c_whenWhereCanCatchTheBall[hashID] =
                    whenWhereCanRobotCatchTheBall_imp1(robot);
        }
        return c_whenWhereCanCatchTheBall[hashID];
    }
    return RobotIntersectTime(INFINITY, Vector2D(INFINITY, INFINITY), robot);
}

float SSLAnalyzer::ballPossession()
{
    float result;
    SSLAnalyzer::RobotIntersectTime  ourRobot = nearestRobotIntersectBall(game->ourColor());
    SSLAnalyzer::RobotIntersectTime  opponentRobot = nearestRobotIntersectBall(game->opponentColor());
    if(ourRobot.isValid() && opponentRobot.isValid())
    {
        if(opponentRobot.m_time > EPS)
            result = ourRobot.m_time/opponentRobot.m_time;
        else
            result = INFINITY;
    }
    if(cmp(result, 1) == 0)
        return 0;
    return log2(result);
}

SSLTeam *SSLAnalyzer::ballPossessorTeam()
{
    float BallPossession = ballPossession();
    if(fabs(BallPossession) < POSSESSION_THRESHOLD)
        return NULL;
    else if(BallPossession <= -POSSESSION_THRESHOLD)
        return game->ourTeam();
    else // if(BallPossession >= POSSESSION_THRESHOLD)
        return game->opponentTeam();
}

// referee states  : Javad
bool SSLAnalyzer::isOurKickOffPosition()
{
    return ((world->m_refereeState == SSLReferee::BlueKickOffPosition && decision->ourColor() == SSL::Blue) ||
            (world->m_refereeState == SSLReferee::YellowKickOffPosition && decision->ourColor() == SSL::Yellow));
}

bool SSLAnalyzer::isOpponentKickOffPosition()
{
    return ((world->m_refereeState == SSLReferee::BlueKickOffPosition && decision->opponentColor() == SSL::Blue) ||
            (world->m_refereeState == SSLReferee::YellowKickOffPosition && decision->opponentColor() == SSL::Yellow));
}

bool SSLAnalyzer::isOurKickOffKick()
{
    return ((world->m_refereeState == SSLReferee::BlueKickOffKick && decision->ourColor() == SSL::Blue) ||
            (world->m_refereeState == SSLReferee::YellowKickOffKick && decision->ourColor() == SSL::Yellow));
}

bool SSLAnalyzer::isOpponentKickOffKick()
{
    return ((world->m_refereeState == SSLReferee::BlueKickOffKick && decision->opponentColor() == SSL::Blue) ||
            (world->m_refereeState == SSLReferee::YellowKickOffKick && decision->opponentColor() == SSL::Yellow));
}

bool SSLAnalyzer::isOurPenaltyPosition()
{
    return ((world->m_refereeState == SSLReferee::BluePenaltyPosition && decision->ourColor() == SSL::Blue) ||
            (world->m_refereeState == SSLReferee::YellowPenaltyPosition && decision->ourColor() == SSL::Yellow));
}

bool SSLAnalyzer::isOpponentPenaltyPosition()
{
    return ((world->m_refereeState == SSLReferee::BluePenaltyPosition && decision->opponentColor() == SSL::Blue) ||
            (world->m_refereeState == SSLReferee::YellowPenaltyPosition && decision->opponentColor() == SSL::Yellow));
}

bool SSLAnalyzer::isOurPenaltyKick()
{
    return ((world->m_refereeState == SSLReferee::BluePenaltyKick && decision->ourColor() == SSL::Blue) ||
            (world->m_refereeState == SSLReferee::YellowPenaltyKick && decision->ourColor() == SSL::Yellow));
}

bool SSLAnalyzer::isOpponentPenaltyKick()
{
    return ((world->m_refereeState == SSLReferee::BluePenaltyKick && decision->opponentColor() == SSL::Blue) ||
            (world->m_refereeState == SSLReferee::YellowPenaltyKick && decision->opponentColor() == SSL::Yellow));
}

bool SSLAnalyzer::isOurDirectKick()
{
    return ((world->m_refereeState == SSLReferee::BlueDirectKick && decision->ourColor() == SSL::Blue) ||
            (world->m_refereeState == SSLReferee::YellowDirectKick && decision->ourColor() == SSL::Yellow));
}

bool SSLAnalyzer::isOpponentDirectKick()
{
    return ((world->m_refereeState == SSLReferee::BlueDirectKick && decision->opponentColor() == SSL::Blue) ||
            (world->m_refereeState == SSLReferee::YellowDirectKick && decision->opponentColor() == SSL::Yellow));
}

bool SSLAnalyzer::isOurIndirectKick()
{
    return ((world->m_refereeState == SSLReferee::BlueIndirectKick && decision->ourColor() == SSL::Blue) ||
            (world->m_refereeState == SSLReferee::YellowIndirectKick && decision->ourColor() == SSL::Yellow));
}

bool SSLAnalyzer::isOpponentIndirectKick()
{
    return ((world->m_refereeState == SSLReferee::BlueIndirectKick && decision->opponentColor() == SSL::Blue) ||
            (world->m_refereeState == SSLReferee::YellowIndirectKick && decision->opponentColor() == SSL::Yellow));
}

bool SSLAnalyzer::isGameRunning()
{
    return m_game_running;
}

// this function should be tested
// I dont trust its functionality: Javad
bool SSLAnalyzer::isPointWithinOurPenaltyArea(Vector2D point)
{
    float our_x = decision->ourSide() * FIELD_LENGTH/2;
    if((point - Vector2D(our_x, FIELD_PENALTY_AREA_WIDTH/2)).lenght() < FIELD_PENALTY_AREA_RADIUS)
        return true;
    if((point - Vector2D(our_x, -FIELD_PENALTY_AREA_WIDTH/2)).lenght() < FIELD_PENALTY_AREA_RADIUS)
        return true;
    if(fabs(point.Y()) < FIELD_PENALTY_AREA_WIDTH/2 && fabs(point.X() - our_x) < FIELD_PENALTY_AREA_RADIUS)
        return true;
    return false;
}

bool SSLAnalyzer::isRobotWithinOurPenaltyArea(Vector3D robot_pos)
{
    float our_x = decision->ourSide() * FIELD_LENGTH/2;
    if((robot_pos.to2D() - Vector2D(our_x, FIELD_PENALTY_AREA_WIDTH/2)).lenght() < FIELD_PENALTY_AREA_RADIUS + ROBOT_RADIUS)
        return true;
    if((robot_pos.to2D() - Vector2D(our_x, -FIELD_PENALTY_AREA_WIDTH/2)).lenght() < FIELD_PENALTY_AREA_RADIUS + ROBOT_RADIUS)
        return true;
    if(fabs(robot_pos.Y()) < FIELD_PENALTY_AREA_WIDTH/2+ROBOT_RADIUS &&
            fabs(robot_pos.X() - our_x) < FIELD_PENALTY_AREA_RADIUS+ROBOT_RADIUS)
        return true;
    return false;
}

bool SSLAnalyzer::isPointInOurSide(const Vector2D &point)
{
    return (point.X() * decision->ourSide() > 0);
}

void SSLAnalyzer::initialize_caches()
{
    memset(f_distance_robot_ball     , 0, sizeof f_distance_robot_ball     );
    memset(f_distance_robot_robot    , 0, sizeof f_distance_robot_robot    );
    memset(f_canKick                 , 0, sizeof f_canKick                 );
    memset(f_whenWhereCanCatchTheBall, 0, sizeof f_whenWhereCanCatchTheBall);
    f_whichRobotCanKick = 0;
}

uint SSLAnalyzer::_getHashID(const SSLRobot *robot)
{
    assert(robot != NULL);
    return robot->id + MAX_ID_NUM*robot->color;
}

bool SSLAnalyzer::isPointWithinOurCorner(const Vector2D &point)
{
    if(isPointWithinOurUpCorner(point))
        return true;
    if(isPointWithinOurDownCorner(point))
        return true;
    return false;
}

bool SSLAnalyzer::isPointWithinOurUpCorner(const Vector2D &point)
{
    float our_x = decision->ourSide() * FIELD_LENGTH/2;
    if(fabs(point.X() - our_x) < 300 && point.Y() > FIELD_WIDTH_2 * .8)
        return true;
    return false;
}

bool SSLAnalyzer::isPointWithinOurDownCorner(const Vector2D &point)
{
    float our_x = decision->ourSide() * FIELD_LENGTH/2;
    if(fabs(point.X() - our_x) < 300 && point.Y() < -FIELD_WIDTH_2 * .8)
        return true;
    return false;
}

Vector2D SSLAnalyzer::ballIntersectionWithOurGoalLine()
{
    LineSegment ball_move_line(world->mainBall()->Position() ,
                               world->mainBall()->Position() + world->mainBall()->Speed() * 5.0/*seconds*/);
    Vector2D ball_intersection_with_goal_line =
            LineSegment::intersection(ball_move_line, SSL::Position::ourGoalLine());
    if( fabs(ball_intersection_with_goal_line.Y()) < INFINITY ) {
        return ball_intersection_with_goal_line;
    }
    else
        return Vector2D(SSL::Position::ourGoalCenter().X(), INFINITY);
}
