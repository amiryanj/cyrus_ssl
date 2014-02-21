#include "SSLAnalyzer.h"

#include "SSLGame.h"
#include "SSLWorldModel.h"
#include "../definition/SSLRobot.h"
#include "../definition/SSLBall.h"

SSLAnalyzer* SSLAnalyzer::analyzer = NULL;

SSLAnalyzer::SSLAnalyzer()
{
    for(int tm=0; tm<2; tm++)
        for(int j=0; j<MAX_ID_NUM; j++)
        {
            this->distToBall[tm][j] = new RobotDistTo(world()->team[tm]->robot[j], world()->ball);
        }
}

SSLAnalyzer* SSLAnalyzer::getInstance()
{
    if(analyzer == NULL)
        analyzer = new SSLAnalyzer();
    return analyzer;
}

SSLWorldModel *SSLAnalyzer::world()
{
    return SSLWorldModel::getInstance();
}

void SSLAnalyzer::check()
{
    // TODO check function    
    updateDistances();
}

double SSLAnalyzer::getTimeToBall(const SSLRobot &robot)
{
    return distToBall[robot.color][robot.id]->getEuclideanTimeToBallSec();
//    return distToBall[robot.color][robot.id]->getManifoldTimeToBallSec();
}

void SSLAnalyzer::updateDistances()
{    
    RobotDistTo::minTimeToBall = RobotDistTo::minTimeToBallOfTeam[0] = RobotDistTo::minTimeToBallOfTeam[1] = INFINITY;
    for(int tm = 0; tm <= 1; ++tm)
        for(unsigned int i=0; i < world()->team[tm]->numInFieldRobots(); ++i )
        {
            distToBall[tm][i]->computeEuclideanToBall();
        }
}

// this function looks for the nearest robot that is able to possess ball among a list of robots
const SSLRobot *SSLAnalyzer::nearestPlayerToBall() const
{
    return RobotDistTo::nearestRobotToBall;
}

const SSLRobot *SSLAnalyzer::nearestPlayerToBall(Color team_color)
{
    return RobotDistTo::nearestRobotToBallOfTeam[team_color];
}

const SSLRobot *SSLAnalyzer::nearestPlayerToBall(vector<SSLRobot*> robots)
{
    double min_time = INFINITY;
    const SSLRobot* nearest;

    for(unsigned int i=0; i<robots.size(); i++)
    {
        SSLRobot* robot = robots.at(i);
        double tmp_time = distToBall[robot->color][robot->id]->getEuclideanTimeToBallSec();
        if(tmp_time < min_time) {
            min_time = tmp_time;
            nearest = robot;
        }
    }
    return nearest;
}

const SSLRobot *SSLAnalyzer::nearestPlayerToPoint(Vector2D point)
{
    return nearestPlayerToPoint(point, world()->all_inFields());
}

const SSLRobot *SSLAnalyzer::nearestPlayerToPoint(Vector2D point, Color team_color)
{
    return nearestPlayerToPoint(point, world()->team[team_color]->inFieldRobots());
}

const SSLRobot *SSLAnalyzer::nearestPlayerToPoint(const Vector2D &point, std::vector<SSLRobot*> robots)
{
    double min_time = INFINITY;
    const SSLRobot* nearest = NULL;
    for(unsigned int i=0; i<robots.size(); ++i)
    {
        double tmp_time = RobotDistTo::distToPoint(robots.at(i), point);
        if(tmp_time < min_time)
        {
            min_time = tmp_time;
            nearest = robots.at(i);
        }
    }
    return nearest;
}

// this function check whether the robot can kick the ball or no
bool SSLAnalyzer::canKick(const SSLRobot *robot)
{
    const double TIME_DIST_FOR_KICK_BALL = 0.2;
    return (distToBall[robot->color][robot->id]->getEuclideanTimeToBallSec() < TIME_DIST_FOR_KICK_BALL);
}

SSLRobot *SSLAnalyzer::inKickPosition(Color team_color)
{
    vector<SSLRobot*> robots = world()->team[team_color]->inFieldRobots();
    if(RobotDistTo::nearestRobotToBall)
    for(unsigned int i = 0; i<robots.size(); i++)
    {
        if(canKick(robots.at(i)))
             return robots.at(i);
    }
    return NULL;
}

/*
 * this function returns a number between [0, 100] where 0 shows
 * that teamA has totally the possession of ball and 100 shows teamB
 * possess the ball
 */
double SSLAnalyzer::possessionRatio(Color team_A, Color team_B)
{
    if(RobotDistTo::minTimeToBallOfTeam[team_A]==0)
        return 100;
    if(RobotDistTo::minTimeToBallOfTeam[team_B]==0)
        return 0;
    double log_ratio = atan(log(RobotDistTo::minTimeToBallOfTeam[team_B] / RobotDistTo::minTimeToBallOfTeam[team_A]));
    return 50 + log_ratio*50.0 / M_PI_2;
}

std::vector<double> SSLAnalyzer::openAnglesToGoal(const Vector2D &point,
                                                Side targetGoalSide, vector<SSLRobot*> defenders)
{
    double origin_angle; // minimum allowed angle in this scop
    Vector2D goalTopCorner, goalDownCorner;
    if(targetGoalSide == Right)    {
        goalTopCorner = Vector2D(FIELD_LENGTH/2, FIELD_GOAL_WIDTH/2);
        goalDownCorner = Vector2D(FIELD_LENGTH/2, -FIELD_GOAL_WIDTH/2);
        origin_angle = -M_PI;
    }
    else    {
        goalTopCorner = Vector2D(-FIELD_LENGTH/2, FIELD_GOAL_WIDTH/2);
        goalDownCorner = Vector2D(-FIELD_LENGTH/2, -FIELD_GOAL_WIDTH/2);
        origin_angle = 0;
    }

//    QLine lineToGoalTopCorner(point, goalTopCorner);
//    QLine lineToGoalDownCorner(point, goalDownCorner);
//    double y_disp_top = double(ROBOT_RADIUS)/cos(lineSlope(lineToGoalTopCorner));
//    double y_disp_down = double(ROBOT_RADIUS)/cos(lineSlope(lineToGoalDownCorner));

//    QPolygon region(4);
//    region[0] = Vector2D(point.x(), point.y() + y_disp_top);
//    region[1] = Vector2D(goalTopCorner.x() , goalTopCorner.y() + y_disp_top);
//    region[2] = Vector2D(goalDownCorner.x() , goalDownCorner.y() - y_disp_down);
//    region[3] = Vector2D(point.x(), point.y() - y_disp_down);

//    double ang_temp_1 = toStandardRadian(lineSlope(lineToGoalTopCorner), origin_angle);
//    double ang_temp_2  = toStandardRadian(lineSlope(lineToGoalDownCorner), origin_angle);
//    double goal_start_angle = qMin(ang_temp_1, ang_temp_2);
//    double goal_end_angle = qMax(ang_temp_1, ang_temp_2);
//    double whole_goal_angle = goal_end_angle - goal_start_angle;

//    std::cerr << "Angle to Goal Without defender"<< (whole_goal_angle/M_PI)*180.0;

//    QList<double> startAngleList;
//    QList<double> endAngleList;

////    for(int i=0; i<worldModel->team[tm]->numInFieldRobots(); ++i)
//    for(int i=0; i<defenders.size(); ++i)
//    {
////        SSLRobot *robot = worldModel->team[tm]->inFieldRobots().at(i);
//        SSLRobot* robot = defenders.at(i);
//        if(region.containsPoint(robot->position.toPoint(), Qt::OddEvenFill))
//        {
//            std::cerr <<"Robot" <<robot->id <<robot->colorStr <<"is in DEFENSE Zone";
//            QLine lineToRobot(point, robot->position.toPoint());
//            double ang_to_robot_center = toStandardRadian(lineSlope(lineToRobot), origin_angle);
//            double diff_angle = asin(ROBOT_RADIUS/Vector2D(lineToRobot.dx(),lineToRobot.dy()).length());
//            ang_temp_1 = ang_to_robot_center + diff_angle;
//            ang_temp_2 = ang_to_robot_center - diff_angle;
//            startAngleList.append(qMin(ang_temp_1, ang_temp_2));
//            endAngleList.append(qMax(ang_temp_1, ang_temp_2));
//        }
//    }
//    // sort the list :|
//    for(int i=0; i<startAngleList.size(); ++i)
//        for(int j=i+1; j<startAngleList.size(); ++j)
//        {
//            if(startAngleList[i] > startAngleList[j])
//            {
//                startAngleList.swap(i,j);
//                endAngleList.swap(i,j);
//            }
//        }

//    // reduce the list bu unioning
//    bool changeExist = true;
//    while(changeExist)
//    {
//        changeExist = false;
//        for(int i=1; i<startAngleList.size(); ++i)
//            if(startAngleList[i]<endAngleList[i-1])
//            {
//                startAngleList.removeAt(i);
//                double tmp_end = qMax(endAngleList[i-1],endAngleList[i]);
//                endAngleList.removeAt(i-1);
//                endAngleList[i-1] = tmp_end;
//                changeExist = true;
//            }
//    }
//    QList<double> open_angles;
//    if(startAngleList.isEmpty())
//    {
//       open_angles <<goal_start_angle << goal_end_angle;
//       return open_angles;
//    }

//    if(startAngleList[0] > goal_start_angle) {
//        open_angles << goal_start_angle << startAngleList[0];
//    }
//    for( int i=0; i < startAngleList.size() - 1; ++i ) {
//        open_angles << endAngleList[i] << startAngleList[i+1];
//    }
//    if(endAngleList.last() < goal_end_angle) {
//        open_angles << endAngleList.last() << goal_end_angle;
//    }
//    return open_angles;
}

double SSLAnalyzer::totalOpenAngle(const Vector2D &point, Side targetGoalSide, std::vector<SSLRobot*> defenders)
{
    std::vector<double> open_angles = openAnglesToGoal(point, targetGoalSide, defenders);
    double totalAngle = 0;
    if(open_angles.size()%2 ==1)
    {
        std::cerr << "DANGEROUS ERROR IN CALCULATION OF OPEN ANGLES" << std::endl;
        return 0;
    }
    for( int i=0; i < open_angles.size() ; i+=2 )
    {
//        totalAngle += open_angles[i+1] - open_angles[i];
    }

    std::cerr << "Total Angle to Goal Side" << targetGoalSide <<
                "is =" << (totalAngle/M_PI) * 180 << "degree" << std::endl;
    return totalAngle;
}




