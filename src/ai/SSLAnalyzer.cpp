#include "SSLAnalyzer.h"

#include "SSLGame.h"
#include "SSLWorldModel.h"
#include "../definition/SSLRobot.h"
#include "../definition/SSLBall.h"

#include <utility>
#include <cmath>

#define defnum 0.1
#define goalposition 3025
#define goalLeftPost 1675
#define goalRightPost 2375
#define robotObstacle 100
#define BALL_FRICTION_COEFF  10.0


SSLAnalyzer* SSLAnalyzer::analyzer_instance = NULL;

SSLAnalyzer::SSLAnalyzer()
{
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
    try {
        if(game->ourTeam()->inFields().empty())
            throw "The team infield attribute is empty.";
        vector<SSLRobot *> defenders  = blockersFromPoint(world->mainBall()->Position());
        if(defenders.empty())
            throw "cannot find any defenders";
        for (int i = 0; i < defenders.size(); i++)
            cout << "defender " << i << " is : " << defenders[i]->id <<  " from team " << defenders[i]->color << endl;
        vector<pair<float, float> > openAngle = openAngleToGoal(world->mainBall()->Position());
        cout << "Angles:" << endl;
        for (int i = 0; i < openAngle.size(); i++)
            cout << openAngle[i].first << " " << openAngle[i].second << endl;
    }
    catch(const char* mes) {
        cerr << "Exception SSLAnalizer : " << mes <<endl;
    }
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
    if(world->mainBall() != NULL && robot != NULL)
        return (world->mainBall()->Position() - robot->Position().to2D()).lenght();
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
    if(robot1 != NULL && robot2 != NULL)
        return (robot1->Position().to2D() - robot2->Position().to2D()).lenght();
    else
        return -1;
}

SSLRobot *SSLAnalyzer::whichRobotCanKick()
{
    vector<SSLRobot* > robots = world->all_inFields();

    for(int  i = 0 ; i < robots.size() ; i ++)
    {
        if(distanceFromBall(robots[i]) < robotObstacle && distanceFromBall(robots[i]) != -1)
        {
            Vector2D dis = world->mainBall()->Position()-robots[i]->Position().to2D();
            double ang = dis.arctan();
            if(fabs(robots[i]->orien() - ang) < (M_PI / 6.0 ) )
            {
                return robots[i];
            }
            else
                continue;
        }
    }
    return NULL;
}

bool SSLAnalyzer::canKick(SSLRobot *robot)
{
    if(distanceFromBall(robot) < (ROBOT_RADIUS * 0.9))
    {
        Vector2D dis = world->mainBall()->Position() - robot->Position().to2D();
        double ang = dis.arctan();
        if(fabs(robot->orien() - ang) < (M_PI / 6.0 ) )
            return true;
        else
            return false;
    }
}


// TODO : Farzad ***************************************************************************
SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToBall(uint index)
{    
    return nearestRobotToBall(world->all_inFields(), index);
}

SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToBall(Color teamColor, uint index)
{
    return nearestRobotToBall(world->getTeam(teamColor)->inFields(), index);
}

SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToBall(const vector<SSLRobot *> &robots, uint index)
{
    vector<RobotIntersectTime> timeForEachRobot;
    if(index >= robots.size()) {
        cerr << "Nearest Robot Could not find";
        return RobotIntersectTime();
    }
    for(uint i = 0 ; i < robots.size(); i++ )
    {
        SSLAnalyzer::RobotIntersectTime res = whenWhereCanRobotCatchTheBall(robots[i]);
        timeForEachRobot.push_back(res);
    }
    sort(timeForEachRobot.begin(), timeForEachRobot.end());
    return timeForEachRobot[index];
}

//----------------------------------------------------------------------------------------------
// TODO : Nariman*****************************************************************************
SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToPoint(const Vector2D &point, uint index)
{
    return nearestRobotToPoint(world->all_inFields(), point, index);
}

SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToPoint(Color teamColor, const Vector2D &point, uint index)
{
    return nearestRobotToPoint(world->getTeam(teamColor)->inFields(), point, index);
}

SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToPoint(const vector<SSLRobot *> &robots, const Vector2D &point, uint index)
{
    if(index > robots.size())
        return NULL;
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
// ------------------------------------------------------------------------------------------
SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToRobot(const SSLRobot *robot, uint index)
{

}
SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToRobot(SSL::Color teamColor, const SSLRobot *robot, uint index)
{

}
SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotToRobot(const vector<SSLRobot *> &robots, const SSLRobot *robot, uint index)
{

}

SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotsToBlockPointOutOfOurPenaltyArea(const Vector2D targetPoint, uint index)
{

}

//--------------------------------------------------------------------------------------------

//blocktrobo
SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotsToBlockPoint(const Vector2D targetPoint, uint index)
{

}

SSLAnalyzer::RobotIntersectTime SSLAnalyzer::nearestRobotsToMarkRobot(const SSLRobot * robot, uint index)
{
    // nearest robot robot :D
}
//point opponentBlockerFromPoint
vector<SSLRobot *> SSLAnalyzer::blockersFromPoint(const Vector2D targetPoint)
{
    SSLRobot* hashed[2 * MAX_ID_NUM];
    memset(hashed, 0, sizeof hashed);
    float r = ROBOT_RADIUS - 2.0;
    int repeat = FIELD_GOAL_WIDTH / (2.0*r);
    for(int i = 0  ; i <= repeat; i ++ )
    {
        float y2 = (-FIELD_GOAL_WIDTH/2.0)+i*2.0*r;
        float xDelta = -(game->ourSide())*FIELD_LENGTH/2.0 - targetPoint.X();
        float m = (y2 - targetPoint.Y()) / xDelta;
        float b = m*(-targetPoint.X());
        vector<SSLRobot*> robots = world->all_inFields();
        for(int j = 0 ; j < robots.size() ; j++)
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
                    hashed[robot->id + 12*robot->color] = robot;
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
    for (int i = 0; i < defenders.size(); i++)
        blockedAngles.push_back(blockedAngleByARobot(targetPoint, defenders[i]));
    blockedAngles.push_back(make_pair(upAngle, upAngle));

    if (game->ourSide() == 1)
        for (int i = 1; i < int(blockedAngles.size()) - 1; i++) {
            blockedAngles[i].first = negativeSideAngleInPositiveSide(blockedAngles[i].first);
            blockedAngles[i].second = negativeSideAngleInPositiveSide(blockedAngles[i].second);
        }

    sort(blockedAngles.begin(), blockedAngles.end());
    vector<pair<float, float> > openAngles;
    int start, last;
    start = 0;
    while (start < blockedAngles.size()) {
        float limit = blockedAngles[start].second;
        last = start + 1;
        if (last == int(blockedAngles.size()))
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
    float cos_theta = cos(Vector2D::angleBetween(diff, robot->Speed().to2D()));
    float wastedTime = (robot->physic.max_lin_vel_mmps - robot->Speed().lenght2D()*cos_theta) / robot->physic.max_lin_acc_mmps2;
    return wastedTime;
}

SSLAnalyzer::RobotIntersectTime SSLAnalyzer::whenWhereCanRobotCatchTheBall_imp1(SSLRobot* robot) {
    /* stop case
     solves using (x-xb)^2 + (y-yb)^2 = r(t)^2 and vb'= at + vb
     r(t): radius robot can be in t seconds from now = ROBOT_MAX_SPEED * t
     */
    RobotIntersectTime stopCaseAnswer;
    stopCaseAnswer.m_robot = robot;

    const SSLBall* ball = world->mainBall();

    float stopTime = fabs(ball->Speed().lenght()) / BALL_FRICTION_COEFF;
    Vector2D newPosition(ball->Position() + ball->Speed() * stopTime);

    float distanceOfNewPositionToRobot = (robot->Position().to2D() - newPosition).lenght();

    float neededTime = distanceOfNewPositionToRobot / robot->physic.max_lin_vel_mmps;
    neededTime += wastedTimeForInertia(robot, newPosition);
    stopCaseAnswer.m_time = neededTime;
    stopCaseAnswer.m_position = newPosition;
    if (ball->Speed().lenght() < 1.0)
        return stopCaseAnswer;
    /* cross case
     solves using (x-xb)^2 + (y-yb)^2 = r(t)^2 and vb = cte
     r(t): radius robot can be in t seconds from now
     there will be an equation like at^2 + bt + c = 0
    */

    RobotIntersectTime crossCaseAnswer;
    crossCaseAnswer.m_robot = robot;

    float xDelta = ball->Position().X() - robot->Position().X();
    float yDelta = ball->Position().Y() - robot->Position().Y();

    float a = (pow(robot->physic.max_lin_vel_mmps, 2.0) - pow(ball->Speed().lenght(), 2.0))/2.0;
    float b = -(ball->Speed().X() * xDelta + ball->Speed().Y() * yDelta);
    float b2_4ac = pow(robot->physic.max_lin_vel_mmps * xDelta, 2.0)
            - pow(ball->Speed().Y() * xDelta ,2.0)
            + 2.0 * ball->Speed().X() * ball->Speed().Y() * xDelta * yDelta
            + pow(robot->physic.max_lin_vel_mmps * yDelta ,2.0)
            - pow(ball->Speed().X() * yDelta ,2.0);

    float neededTime1 = (-b + sqrt(b2_4ac))/(2.0*a);
    float neededTime2 = (-b - sqrt(b2_4ac))/(2.0*a);

    Vector2D newPosition1 = Vector2D(ball->Position() + ball->Speed() * neededTime1);
    Vector2D newPosition2 = Vector2D(ball->Position() + ball->Speed() * neededTime2);

    neededTime = min(neededTime1 + wastedTimeForInertia(robot, newPosition1),
                     neededTime2 + wastedTimeForInertia(robot, newPosition2));

    crossCaseAnswer.m_time = neededTime;
    crossCaseAnswer.m_position = newPosition;

    /*
     compare both cases and return best answer
     */

    if (stopCaseAnswer.m_time < crossCaseAnswer.m_time)
        return stopCaseAnswer;
    return crossCaseAnswer;
}

SSLAnalyzer::RobotIntersectTime SSLAnalyzer::whenWhereCanRobotCatchTheBall(SSLRobot* robot) {
    const SSLBall* ball = world->mainBall();

    if (robot && ball) {
        return whenWhereCanRobotCatchTheBall_imp1(robot);
    }
    return RobotIntersectTime(INFINITY, Vector2D(INFINITY, INFINITY), robot);
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
bool SSLAnalyzer::isPointWithinOurPenaltyArea(const Vector2D &point)
{
    float our_x = decision->ourSide() * FIELD_LENGTH/2;
    if((point - Vector2D(our_x, FIELD_PENALTY_AREA_WIDTH/2)).lenght() < FIELD_PENALTY_AREA_RADIUS)
        return true;
    if((point - Vector2D(our_x, -FIELD_PENALTY_AREA_WIDTH/2)).lenght() < FIELD_PENALTY_AREA_RADIUS)
        return true;
    if(fabs(point.Y()) < FIELD_PENALTY_AREA_WIDTH/2 &&
            fabs(point.X()) > (decision->ourSide() * (FIELD_LENGTH - FIELD_PENALTY_AREA_RADIUS )) &&
            isPointInOurSide(point))
        return true;
    return false;
}

bool SSLAnalyzer::isPointInOurSide(const Vector2D &point)
{
    return (point.X() * decision->ourSide() > 0);
}

