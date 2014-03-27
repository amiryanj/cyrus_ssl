#include "SSLAnalyzer.h"

#include "SSLGame.h"
#include "SSLWorldModel.h"
#include "../definition/SSLRobot.h"
#include "../definition/SSLBall.h"

#include <utility>
#include <algorithm>
#include <cmath>
#include <algorithm>

#define defnum 0.1
#define goalposition 3025
#define goalLeftPost 1675
#define goalRightPost 2375
#define robotObstacle 100

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
    // TODO check function
    if(m_game_running) {
        if(world->m_refereeState == SSLReferee::Stop || world->m_refereeState == SSLReferee::Halt){
            m_game_running = false;
        }
    }
    else {
        if(world->m_refereeState == SSLReferee::ForceStart)
            m_game_running = true;
        SSLReferee::RefereeState st = world->m_refereeState;
        if( st == SSLReferee::BlueDirectKick   || st == SSLReferee::YellowDirectKick   ||
            st == SSLReferee::BlueIndirectKick || st == SSLReferee::YellowIndirectKick ||
            st == SSLReferee::BlueKickOffKick  || st == SSLReferee::YellowKickOffKick  ||
            st == SSLReferee::BluePenaltyKick  || st == SSLReferee::YellowPenaltyKick )
       {
//            vector<SSLRobot* > nears = nearestRobotToBall(world->all_inFields());
//            if(nears.empty())
//                return;
//            SSLRobot* near = nears[0];
//            double diff2Ball = (near->Position().to2D() - world->mainBall()->Position()).lenght();
//            if(diff2Ball < (BALL_RADIUS + ROBOT_RADIUS))

            if(world->mainBall()->Speed().lenght() > 200) { // milimeter/sec
                m_game_running = true;
            }
       }
    }
}

//double SSLAnalyzer::getTimeToBall(const SSLRobot &robot)
//{
//    return distToBall[robot.color][robot.id]->getEuclideanTimeToBallSec();
////    return distToBall[robot.color][robot.id]->getManifoldTimeToBallSec();
//}

//void SSLAnalyzer::updateDistances()
//{
//    RobotDistTo::minTimeToBall = RobotDistTo::minTimeToBallOfTeam[0] = RobotDistTo::minTimeToBallOfTeam[1] = INFINITY;
//    for(int tm = 0; tm <= 1; ++tm)
//        for(unsigned int i=0; i < world->team[tm]->numInFieldRobots(); ++i )
//        {
//            distToBall[tm][i]->computeEuclideanToBall();
//        }
//}

//// this function looks for the nearest robot that is able to possess ball among a list of robots
//const SSLRobot *SSLAnalyzer::nearestPlayerToBall() const
//{
//    return RobotDistTo::nearestRobotToBall;
//}

//const SSLRobot *SSLAnalyzer::nearestPlayerToBall(Color team_color)
//{
//    return RobotDistTo::nearestRobotToBallOfTeam[team_color];
//}

//const SSLRobot *SSLAnalyzer::nearestPlayerToBall(vector<SSLRobot*> robots)
//{
//    double min_time = INFINITY;
//    const SSLRobot* nearest;

//    for(unsigned int i=0; i<robots.size(); i++)
//    {
//        SSLRobot* robot = robots.at(i);
//        double tmp_time = distToBall[robot->color][robot->id]->getEuclideanTimeToBallSec();
//        if(tmp_time < min_time) {
//            min_time = tmp_time;
//            nearest = robot;
//        }
//    }
//    return nearest;
//}

//const SSLRobot *SSLAnalyzer::nearestPlayerToPoint(Vector2D point)
//{
//    return nearestPlayerToPoint(point, world->allRobots());
//}

//const SSLRobot *SSLAnalyzer::nearestPlayerToPoint(Vector2D point, Color team_color)
//{
//    return nearestPlayerToPoint(point, world->team[team_color]->inFieldRobots());
//}

//const SSLRobot *SSLAnalyzer::nearestPlayerToPoint(const Vector2D &point, std::vector<SSLRobot*> robots)
//{
//    double min_time = INFINITY;
//    const SSLRobot* nearest = NULL;
//    for(unsigned int i=0; i<robots.size(); ++i)
//    {
//        double tmp_time = RobotDistTo::distToPoint(robots.at(i), point);
//        if(tmp_time < min_time)
//        {
//            min_time = tmp_time;
//            nearest = robots.at(i);
//        }
//    }
//    return nearest;
//}

//// this function check whether the robot can kick the ball or no
//bool SSLAnalyzer::canKick(std::vector<SSLRobot*> robots)
//{
//    const SSLRobot *roboHaveball = robotHaveBall(robots);
//    double x;
//    if(roboHaveball->color == SSLGame::getInstance()->ourColor())
//    {
//        goalposition *= SSLGame::getInstance()->enemySide();
//        x = ((goalposition - roboHaveball->Position().Y())/(((roboHaveball->Position().Y() - world->ball->Position().Y())/(roboHaveball->Position().X() - world->ball->Position().X()))) + (roboHaveball->Position().X()));
//        if(x >= goalLeftPost && x <= goalRightPost)
//            return true;
//        else
//            return false;
//    }
//    else
//    {
//        goalposition *= SSLGame::getInstance()->ourSide();
//        x = ((goalposition - roboHaveball->Position().Y())/(((roboHaveball->Position().Y() - world->ball->Position().Y())/(roboHaveball->Position().X() - world->ball->Position().X()))) + (roboHaveball->Position().X()));
//        if(x >= goalLeftPost && x <= goalRightPost)
//            return true;
//        else
//            return false;
//    }
//}

////this function check that whether the rival robot can make a goal or no
//bool SSLAnalyzer::canRivalMakeAGoal(std::vector<SSLRobot*> robots)
//{
//    const SSLRobot *roboHaveball = robotHaveBall(robots);
//    if(roboHaveball->color == SSLGame::getInstance()->ourColor())
//        return false;
//    else
//    {
//        double x;
//        goalposition *= SSLGame::getInstance()->ourSide();
//        x = ((goalposition - roboHaveball->Position().Y())/(((roboHaveball->Position().Y() - world->ball->Position().Y())/(roboHaveball->Position().X() - world->ball->Position().X()))) + (roboHaveball->Position().X()));
//        if(x >= goalLeftPost && x <= goalRightPost)
//            return true;
//        else
//            return false;
//    }
//}

//bool SSLAnalyzer::havingBall(std::vector<SSLRobot*> robots)
//{
//    for(unsigned int i=0; i<robots.size(); i++)
//    {
//        SSLRobot *robo = robots.at(i);
//        double robox = robo->Position().X();
//        double roboy = robo->Position().Y();
//        double distoball = sqrt(pow((robox - world->ball->Position().X()),2) + sqrt(pow((roboy - world->ball->Position().Y()),2)));
//        if(robo->radius > distoball)
//        {
//            Vector2D dis = world->ball->Position()-robo->Position().to2D();
//            double ang = atan(dis.Y()/dis.X());
//            if(((robo->orien()- ang ) < defnum ))
//            {
//                if(robo->color == SSLGame::getInstance()->ourColor())
//                    return true;
//                return false;
//            }
//            else
//                continue;
//        }
//        else
//            continue;
//    }
//    return false;
//}

//const SSLRobot *SSLAnalyzer::robotHaveBall(std::vector<SSLRobot*> robots)
//{
//    for(unsigned int i=0; i<robots.size(); i++)
//    {
//        SSLRobot *robo = robots.at(i);

//        double robox = robo->Position().X();
//        double roboy = robo->Position().Y();
//        double distoball = sqrt(pow((robox - world->ball->Position().X()),2) + sqrt(pow((roboy - world->ball->Position().Y()),2)));
//        if(robo->radius > distoball)
//        {
//            Vector2D dis = world->ball->Position()-robo->Position().to2D();
//            double ang = atan(dis.Y()/dis.X());
//            if(((robo->orien()- ang) < defnum ))
//            {
//                return robo;
//            }
//            else
//                continue;
//        }
//        else
//            continue;
//    }
//    return NULL;
//}

//const SSLRobot *SSLAnalyzer::nearestPlayerToBlock(std::vector<SSLRobot*> robots)
//{
//    double min = INFINITY;
//    const SSLRobot* nearest = NULL;
//    const SSLRobot *roboHaveball = robotHaveBall(robots);
//    for(unsigned int i = 0; i < robots.size(); i++)
//    {
//        SSLRobot *robo = robots.at(i);
//        if(robo->color == roboHaveball->color && robo->id == roboHaveball->id)
//            continue;
//        else if(robo->color != SSLGame::getInstance()->ourColor())
//            continue;
//        else
//        {

//            double robox = robo->Position().X();
//            double roboy = robo->Position().Y();
//            double distoball = sqrt(pow((robox - world->ball->Position().X()),2) + sqrt(pow((roboy - world->ball->Position().Y()),2)));
//            if(distoball < min)
//            {
//              nearest = robo;
//              min = distoball;
//            }
//        }
//    }
//    return nearest;
//}

///*
// * this function returns a number between [0, 100] where 0 shows
// * that teamA has totally the possession of ball and 100 shows teamB
// * possess the ball
// */
//double SSLAnalyzer::possessionRatio(Color team_A, Color team_B)
//{
//    if(RobotDistTo::minTimeToBallOfTeam[team_A]==0)
//        return 100;
//    if(RobotDistTo::minTimeToBallOfTeam[team_B]==0)
//        return 0;
//    double log_ratio = atan(log(RobotDistTo::minTimeToBallOfTeam[team_B] / RobotDistTo::minTimeToBallOfTeam[team_A]));
//    return 50 + log_ratio*50.0 / M_PI_2;
//}

//std::vector<double> SSLAnalyzer::openAnglesToGoal(const Vector2D &point,
//                                                Side targetGoalSide, vector<SSLRobot*> defenders)
//{
//    double origin_angle; // minimum allowed angle in this scop
//    Vector2D goalTopCorner, goalDownCorner;
//    if(targetGoalSide == Right)    {
//        goalTopCorner = Vector2D(FIELD_LENGTH/2, FIELD_GOAL_WIDTH/2);
//        goalDownCorner = Vector2D(FIELD_LENGTH/2, -FIELD_GOAL_WIDTH/2);
//        origin_angle = -M_PI;
//    }
//    else    {
//        goalTopCorner = Vector2D(-FIELD_LENGTH/2, FIELD_GOAL_WIDTH/2);
//        goalDownCorner = Vector2D(-FIELD_LENGTH/2, -FIELD_GOAL_WIDTH/2);
//        origin_angle = 0;
//    }

////    QLine lineToGoalTopCorner(point, goalTopCorner);
////    QLine lineToGoalDownCorner(point, goalDownCorner);
////    double y_disp_top = double(ROBOT_RADIUS)/cos(lineSlope(lineToGoalTopCorner));
////    double y_disp_down = double(ROBOT_RADIUS)/cos(lineSlope(lineToGoalDownCorner));

////    QPolygon region(4);
////    region[0] = Vector2D(point.x(), point.y() + y_disp_top);
////    region[1] = Vector2D(goalTopCorner.x() , goalTopCorner.y() + y_disp_top);
////    region[2] = Vector2D(goalDownCorner.x() , goalDownCorner.y() - y_disp_down);
////    region[3] = Vector2D(point.x(), point.y() - y_disp_down);

////    double ang_temp_1 = toStandardRadian(lineSlope(lineToGoalTopCorner), origin_angle);
////    double ang_temp_2  = toStandardRadian(lineSlope(lineToGoalDownCorner), origin_angle);
////    double goal_start_angle = qMin(ang_temp_1, ang_temp_2);
////    double goal_end_angle = qMax(ang_temp_1, ang_temp_2);
////    double whole_goal_angle = goal_end_angle - goal_start_angle;

////    std::cerr << "Angle to Goal Without defender"<< (whole_goal_angle/M_PI)*180.0;

////    QList<double> startAngleList;
////    QList<double> endAngleList;

//////    for(int i=0; i<worldModel->team[tm]->numInFieldRobots(); ++i)
////    for(int i=0; i<defenders.size(); ++i)
////    {
//////        SSLRobot *robot = worldModel->team[tm]->inFieldRobots().at(i);
////        SSLRobot* robot = defenders.at(i);
////        if(region.containsPoint(robot->position.toPoint(), Qt::OddEvenFill))
////        {
////            std::cerr <<"Robot" <<robot->id <<robot->colorStr <<"is in DEFENSE Zone";
////            QLine lineToRobot(point, robot->position.toPoint());
////            double ang_to_robot_center = toStandardRadian(lineSlope(lineToRobot), origin_angle);
////            double diff_angle = asin(ROBOT_RADIUS/Vector2D(lineToRobot.dx(),lineToRobot.dy()).length());
////            ang_temp_1 = ang_to_robot_center + diff_angle;
////            ang_temp_2 = ang_to_robot_center - diff_angle;
////            startAngleList.append(qMin(ang_temp_1, ang_temp_2));
////            endAngleList.append(qMax(ang_temp_1, ang_temp_2));
////        }
////    }
////    // sort the list :|
////    for(int i=0; i<startAngleList.size(); ++i)
////        for(int j=i+1; j<startAngleList.size(); ++j)
////        {
////            if(startAngleList[i] > startAngleList[j])
////            {
////                startAngleList.swap(i,j);
////                endAngleList.swap(i,j);
////            }
////        }

////    // reduce the list bu unioning
////    bool changeExist = true;
////    while(changeExist)
////    {
////        changeExist = false;
////        for(int i=1; i<startAngleList.size(); ++i)
////            if(startAngleList[i]<endAngleList[i-1])
////            {
////                startAngleList.removeAt(i);
////                double tmp_end = qMax(endAngleList[i-1],endAngleList[i]);
////                endAngleList.removeAt(i-1);
////                endAngleList[i-1] = tmp_end;
////                changeExist = true;
////            }
////    }
////    QList<double> open_angles;
////    if(startAngleList.isEmpty())
////    {
////       open_angles <<goal_start_angle << goal_end_angle;
////       return open_angles;
////    }

////    if(startAngleList[0] > goal_start_angle) {
////        open_angles << goal_start_angle << startAngleList[0];
////    }
////    for( int i=0; i < startAngleList.size() - 1; ++i ) {
////        open_angles << endAngleList[i] << startAngleList[i+1];
////    }
////    if(endAngleList.last() < goal_end_angle) {
////        open_angles << endAngleList.last() << goal_end_angle;
////    }
////    return open_angles;
//}

//double SSLAnalyzer::totalOpenAngle(const Vector2D &point, Side targetGoalSide, std::vector<SSLRobot*> defenders)
//{
//    std::vector<double> open_angles = openAnglesToGoal(point, targetGoalSide, defenders);
//    double totalAngle = 0;
//    if(open_angles.size()%2 ==1)
//    {
//        std::cerr << "DANGEROUS ERROR IN CALCULATION OF OPEN ANGLES" << std::endl;
//        return 0;
//    }
//    for( int i=0; i < open_angles.size() ; i+=2 )
//    {
////        totalAngle += open_angles[i+1] - open_angles[i];
//    }

//    std::cerr << "Total Angle to Goal Side" << targetGoalSide <<
//                "is =" << (totalAngle/M_PI) * 180 << "degree" << std::endl;
//    return totalAngle;
//}




int SSLAnalyzer::distanceFromBall(Vector2D point)
{
    return (world->mainBall()->Position() - point).lenght();
}
int SSLAnalyzer::distanceFromBall(SSLRobot* robot)
{
    return sqrt(((world->mainBall()->Position().X() - robot->Position().X())*(world->mainBall()->Position().X() - robot->Position().X()))
              + ((world->mainBall()->Position().Y() - robot->Position().Y())*(world->mainBall()->Position().Y() - robot->Position().Y())));
}

int SSLAnalyzer::distanceFromRobotToPoint(Vector2D point, SSLRobot* robot)
{
    return (robot->Position().to2D() - point).lenght();
}
int SSLAnalyzer::distanceFromRobotToRobot(SSLRobot* robot1,SSLRobot* robot2)
{
    return sqrt(((robot1->Position().X() - robot2->Position().X())*(robot1->Position().X() - robot2->Position().X()))
              + ((robot1->Position().Y() - robot2->Position().Y())*(robot1->Position().Y() - robot2->Position().Y())));
}

// TODO Nariman
bool SSLAnalyzer::canKick(SSLRobot* robot)
{
    //
}

// TODO Nariman
SSLRobot *SSLAnalyzer::whichRobotCanKick()
{
}

std::vector<SSLRobot*> SSLAnalyzer::nearestRobotToBall(std::vector<SSLRobot*> robots)
{
//    vector<pair<SSLRobot*, int> > robotDistanceFromBall;
//    for(int i = 0 ; i < robots.size() ; i ++)
//    {
//        robotDistanceFromBall[i].first = robots.at(i);
//        robotDistanceFromBall[i].second = distanceFromBall(robots.at(i));
//    }
//    sort(robotDistanceFromBall.begin(), robotDistanceFromBall.end(), mySort);
}

std::vector<SSLRobot*> SSLAnalyzer::nearestRobotToPoint(std::vector<SSLRobot *> robots, Vector2D point)
{
//    vector<pair<SSLRobot*,int> > robotDistanceFromPoint;
//    for(int i = 0 ; i < robots.size() ; i ++)
//    {
//        robotDistanceFromPoint[i].first = robots.at(i);
//        robotDistanceFromPoint[i].second = distanceFromRobotToPoint(point,robots.at(i));
//    }
//    sort(robotDistanceFromPoint.begin(), robotDistanceFromPoint.end(), mySort);
}

std::vector<SSLRobot*> SSLAnalyzer::nearestRobotToRobot(std::vector<SSLRobot *> robots, SSLRobot *robot)
{
//    vector<pair<SSLRobot*,int> > robotDistanceFromRobot;
//    for(int i = 0 ; i < robots.size() ; i ++)
//    {
//        robotDistanceFromRobot[i].first = robots.at(i);
//        robotDistanceFromRobot[i].second = distanceFromRobotToRobot(robot,robots.at(i));
//    }
//    sort(robotDistanceFromRobot.begin(), robotDistanceFromRobot.end(), mySort);
}

bool SSLAnalyzer::isRobotAhead(SSLRobot * robot1, SSLRobot * robot2)
{
    if(robot1->Position().X() > robot2->Position().X())
        return true;
    else
        return false;
}

bool SSLAnalyzer::isRobotSameSide(SSLRobot * robot1, SSLRobot * robot2)
{
    if(robot1->Position().Y() < FIELD_WIDTH/2 && robot2->Position().Y() < FIELD_WIDTH/2)
        return true;
    else if(robot1->Position().Y() > FIELD_WIDTH/2 && robot2->Position().Y() > FIELD_WIDTH/2)
        return true;
    else
        return false;
}

// it doesnt work ...
std::vector<SSLRobot*> SSLAnalyzer::cyrusCanMakePass()
{
    vector<SSLRobot*> our_robots = decision->ourTeam()->inFields();
    SSLRobot* in_kick_position = whichRobotCanKick();
    if(in_kick_position == NULL) {
        vector<SSLRobot* > empty_vector;
        return empty_vector;
    }

    //    for(vector<SSLRobot*>::iterator it = our_robots.begin(); it != our_robots.end(); it++)
//    for(int i = our_robots.size() - 1; i >= 0; i--)
//    {
//        line = new Qline((int)RobotCanKick->Position().X(),(int)RobotCanKick->Position().Y(),(int)our_robots[i]->Position().X(),(int)our_robots[i]->Position().Y());
//        int m  = line->dy()/line->dx();
//        int b = RobotCanKick->Position().Y() - m*RobotCanKick->Position().X();
//        for(int j = 0 ; j < opponentRobots.size() ; j++ )
//        {
//            if(opponentRobots[j]->Position().Y() == m*(opponentRobots[j]->Position().X()) + b)
//                our_robots.erase(i);
//        }
//        for(int j = 0 ; j < cyrusRobots.size() ; j++ )
//        {
//            if(cyrusRobots[j]->Position().Y() == m*(cyrusRobots[j]->Position().X()) + b)
//                our_robots.erase(i);
//        }
//    }
    // makePriorityVector(std::vector<SSLRobot*> tempCyrusRobot)
}

// it doesnt work ...
std::vector<SSLRobot*> SSLAnalyzer::opponentCanMakePass(std::vector<SSLRobot*> cyrusRobots,std::vector<SSLRobot*> opponentRobots)
{
//    std::vector<SSLRobot*> tempOpponentRobot = opponentRobots;
//    SSLRobot * RobotHaveBall = robotHaveBall(tempOpponentRobot);
//    SSLRobot * RobotCanKick = robotCanKick(RobotHaveBall);
//    for(int i = 0 ; i < tempOpponentRobot.size() ; i ++)
//    {
//        QLine * line = new Qline((int)RobotCanKick->Position().X(),(int)RobotCanKick->Position().Y(),(int)tempOpponentRobot[i]->Position().X(),(int)tempOpponentRobot[i]->Position().Y());
//        int m  = line->dy()/line->dx();
//        int b = RobotCanKick->Position().Y() - m*RobotCanKick->Position().X();
//        for(int j = 0 ; j < opponentRobots.size() ; j++ )
//        {
//            if(opponentRobots[j]->Position().Y() == m*(opponentRobots[j]->Position().X()) + b)
//                tempOpponentRobot.erase(i);
//        }
//        for(int j = 0 ; j < cyrusRobots.size() ; j++ )
//        {
//            if(cyrusRobots[j]->Position().Y() == m*(cyrusRobots[j]->Position().X()) + b)
//                tempOpponentRobot.erase(i);
//        }
//    }
      // makePriorityVector(std::vector<SSLRobot*> tempCyrusRobot)    
}

SSLRobot* SSLAnalyzer::cyrusCanMakeGoal(std::vector<SSLRobot *> cyrusRobots, std::vector<SSLRobot *> opponentRobots, std::vector<int>& goalPoints)
{
//    SSLRobot* RobotHaveBall = robotHaveBall(cyrusRobots);
//    SSLRobot* RobotCanKick  = robotCanKick(RobotHaveBall);
//    int k = 0 ;
//    for(int i = 0 ; i < (int)FIELD_GOAL_WIDTH/(world->ball->radius*2) ; i ++  )
//    {
//        QLine * line = new QLine(RobotCanKick->Position().X(),RobotCanKick->Position().Y(),(FIELD_LENGTH/2)*SSLGame::getInstance()->ourSide(),i*(world->ball->radius*2)+(-FIELD_GOAL_WIDTH/2));
//        int m  = line->dy()/line->dx();
//        int b = RobotCanKick->Position().Y() - m*RobotCanKick->Position().X();
//        for(int j = 0 ; j < opponentRobots.size() ; j++ )
//        {
//            if(opponentRobots[j]->Position().Y() == m*(opponentRobots[j]->Position().X()) + b)
//                return NULL;
//        }
//        for(int j = 0 ; j < cyrusRobots.size() ; j++ )
//        {
//            if(cyrusRobots[j]->Position().Y() == m*(cyrusRobots[j]->Position().X()) + b)
//                return NULL;
//        }
//        goalPoints[k++] = i*(world->ball->radius*2)+(-FIELD_GOAL_WIDTH/2);
//        return RobotCanKick;
//    }
}

SSLRobot* SSLAnalyzer::opponentCanMakeGoal(std::vector<SSLRobot *> cyrusRobots, std::vector<SSLRobot *> opponentRobots, std::vector<int>& goalPoints)
{ 
//    SSLRobot* RobotHaveBall = robotHaveBall(opponentRobots);
//    SSLRobot* RobotCanKick  = robotCanKick(RobotHaveBall);
//    int k = 0;
//    for(int i = 0 ; i < (int)FIELD_GOAL_WIDTH/(world->ball->radius*2) ; i ++  )
//    {
//        QLine * line = new QLine(RobotCanKick->Position().X(),RobotCanKick->Position().Y(),(FIELD_LENGTH/2)*SSLGame::getInstance()->ourSide(),i*(world->ball->radius*2)+(-FIELD_GOAL_WIDTH/2));
//        int m  = line->dy()/line->dx();
//        int b = RobotCanKick->Position().Y() - m*RobotCanKick->Position().X();
//        for(int j = 0 ; j < opponentRobots.size() ; j++ )
//        {
//            if(opponentRobots[j]->Position().Y() == m*(opponentRobots[j]->Position().X()) + b)
//                return NULL;
//        }
//        for(int j = 0 ; j < cyrusRobots.size() ; j++ )
//        {
//            if(cyrusRobots[j]->Position().Y() == m*(cyrusRobots[j]->Position().X()) + b)
//                return NULL;
//        }
//        goalPoints[k++] = i*(world->ball->radius*2)+(-FIELD_GOAL_WIDTH/2);
//        return RobotCanKick;
//    }
}

std::vector<SSLRobot*> SSLAnalyzer::nearestRobotsToBlockRobot(std::vector<SSLRobot*> cyrusRobots,std::vector<SSLRobot*> opponentRobots)
{
//    std::vector<int> goalYPoints;
//    SSLRobot * robot = opponentCanMakeGoal(cyrusRobots,opponentRobots,goalYPoints);
//    QLine * line = new QLine(robot->Position().X() , robot->Position().Y() , world->ball->Position().X(),world->ball->Position().Y());

//    int m = line->dy()/line->dx();

//    int b = world->ball->Position().Y() - m*world->ball->Position().X();

//    vector<pair<SSLRobot*,int> > distancesFromLine;
//    vector<SSLRobot *> returnVector;
//    distances.resize(cyrusRobots.size());
//    for(int  i = 0 ; i < cyrusRobots.size() ; i ++)
//    {
//        SSLRobot *Robot = cyrusRobots.at(i);
//        int m1 = -1/m;
//        int b1 = Robot->Position().Y() - m1*(Robot->Position().X());

//        int x = (b-b1)/(m1-m);

//        int y = m1x + b1;
//        distancesFromLine[i].first = Robot;
//        distancesFromLine[i].second = sqrt((Robot->Position().X() - x)*(Robot->Position().X() - x) + (Robot->Position().Y() - y)*(Robot->Position().Y() - y));
//    }

//    sort(distancesFromLine.begin(),distancesFromLine.end(),mySort);
//    for(vector<pair<SSLRobot*,int> >::iterator iter = distancesFromLine.begin(); iter != distancesFromLine.end(); iter++ )
//    {
//        returnVector.push_back(iter->first);
//    }
//    return returnVector;
}
std::vector<SSLRobot*> SSLAnalyzer::nearestRobotsToMarkRobot(std::vector<SSLRobot*> cyrusRobots,std::vector<SSLRobot*> opponentRobots)
{
//    std::vector<int> distances;
//    distances.resize(cyrusRobots.size());
//    SSLRobot * robot = robotHaveBall(opponentRobots);
//    for(int i = 0 ; i < cyrusRobots.size() ; i ++)
//    {
//        distances[i] = distanceFromRobotToRobot(robot,cyrusRobots[i]);
//    }

    //sort ...
}

float SSLAnalyzer::distToCatchBall(SSLRobot *robot)
{
    // simplest implementation,
    // just works when the ball is stopped
    return this->distanceFromBall(robot);
}

Vector2D SSLAnalyzer::whereCanCatchBall(SSLRobot *robot)
{
    // simplest implementation,
    // just works when the ball is stopped
    return world->mainBall()->Position();
}

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

bool SSLAnalyzer::mySort(pair<SSLRobot *, int> i, pair<SSLRobot *, int> j)
{
    if(i.second < j.second)
        return true;
    if(j.second < i.second)
        return false;
}

