#include "SSLAnalyzer.h"

#include "SSLGame.h"
//#include "SSLMath.h"
//#include <QRegion>
//#include <QLine>
//#include <QPolygon>

SSLAnalyzer* SSLAnalyzer::analyzer=NULL;

SSLAnalyzer::SSLAnalyzer()
{
    world = SSLWorldModel::getInstance();
}

SSLAnalyzer* SSLAnalyzer::getInstance()
{
    if(analyzer == NULL)
        analyzer = new SSLAnalyzer();
    return analyzer;
}

void SSLAnalyzer::check()
{
    // TODO check function
}

void SSLAnalyzer::updateAllAccessTimes()
{
    SSLBall* ball = world->ball;
    for(int tm = 0; tm <= 1; ++tm)
        for(int i=0; i < world->team[tm]->numInFieldRobots(); ++i )
        {
            SSLRobot* robot = world->team[tm]->inFieldRobots().at(i);
            double acc_time = calcAccessTime(robot, ball);
            Vector2D acc_int = ball->Position()+ ball->Speed() * acc_time;
            access_time[tm][robot->id] = acc_time;
            access_intercept[tm][robot->id] = acc_int;
            std::cerr << "Access time: robot(" << robot->id << ")" << world->team[tm]->colorStr()
                  << "=" << acc_time << ", Intercept: x=" << acc_int.X() << "y=" << acc_int.Y() << std::endl;
        }
}

double SSLAnalyzer::calcAccessTime(SSLRobot *robot, SSLBall *ball)
{
    double t_est = 0;
    Vector2D intercept;
    double t_lim1 = (robot->physic.max_lin_vel - robot->Speed().lenght2D())
                            /robot->physic.max_lin_acc;
    double t_lim2 = (robot->physic.max_lin_vel + robot->Speed().lenght2D())
                            /robot->physic.max_lin_acc;
    if(robot->id == 1) // test robot 1
        { std::cerr << "Time to MAX speed:" << t_lim1 << ", Time to MIN speed" << t_lim2 << std::endl; }
    for(double t_Low=0, t_High=4.0; ; ) // in sec
    {
        double t_range = t_High - t_Low;
        Vector2D center0 = robot->Position().to2D() + robot->Speed().to2D() * t_High ;
        Vector2D center1;
        double forw_disp, backw_disp, radius;

        if(t_High < t_lim1)
        {
            center1 = center0 ;
            radius = t_High * t_High * robot->physic.max_lin_acc / 2.0;
        }
        else if(t_High < t_lim2)
        {
            forw_disp = robot->physic.max_lin_acc * (t_lim1 * t_lim1) / 2.0
                    + robot->physic.max_lin_vel * (t_High - t_lim1) ;
            backw_disp = robot->physic.max_lin_acc * (t_High * t_High ) / 2.0;
            radius = (forw_disp + backw_disp)/2.0;
            center1 = center0 + robot->Speed().normalized2D() * (forw_disp - backw_disp);
        }
        else
        {
            forw_disp = robot->physic.max_lin_acc * (t_lim1 * t_lim1) / 2.0
                    + robot->physic.max_lin_vel * (t_High - t_lim1) ;
            backw_disp = robot->physic.max_lin_acc * (t_lim2 * t_lim2 ) / 2.0
                    + robot->physic.max_lin_vel * (t_High - t_lim2) ;
            radius = (forw_disp + backw_disp)/2.0;
            center1 = center0 + robot->Speed().normalized2D() * (forw_disp - backw_disp);
        }

//        QRegion region(1000.0*(center1.x()-radius/2),1000.0*(center1.y()-radius/2),
//                               1000.0*2.0*radius, 1000.0*2.0* radius, QRegion::Ellipse);

//        Vector2D point = (1000.0*(ball->position + t_High * ball->speed).toPoint());
//        if(!region.contains(point))
        if(!((ball->Position() + ball->Speed() * t_High - center1).lenght()
                            <= radius + robot->physic.radius + ball->radius))

             t_Low = t_High;

        t_High = t_Low + t_range/2.0 ;
        if((t_High - t_Low) < 0.002 )  // precision = 1 ms
        {
            t_est = (t_High + t_Low)/2;
            intercept = ball->Position() + ball->Speed() * t_est;
            break;
        }
    }

    double rot = angleForRotate(robot, intercept);
    t_est += abs(rot/robot->physic.max_ang_vel);
    return t_est;
}

SSLRobot* SSLAnalyzer::nearestPlayer(SSLTeam* team)
{
    SSLRobot* nearest;
    double min_time = 10.00; // max time to get ball
    if( team->numInFieldRobots()==0 )
    {
        std::cerr << "No robot in team " << team->colorStr() << std::endl ;
        return NULL;
    }

    for(int i=0; i < team->numInFieldRobots(); ++i)
    {
        SSLRobot* robot = team->inFieldRobots().at(i);
        //double acc_time = calcAccessTime(robot, worldModel->ball);
        double acc_time = access_time[(int)team->color][robot->id];
        if( acc_time < min_time)
        {
            min_time = acc_time;
            nearest = robot;
        }
    }
    std::cerr << "Nearest Player[" << nearest->colorStr() << "] is:" << nearest->id << std::endl;
    return nearest;
}

double SSLAnalyzer::possessionRatio()
{
    double min_time[2];
    for(int tm = 0; tm <=1; ++tm)
       { min_time[tm] = minAccessTime(world->team[tm]); }


    int our_color = (int) SSLGame::getInstance()->ourColor();
    double p_ratio = min_time[1 - our_color] / min_time[our_color];
    return p_ratio;
}

double SSLAnalyzer::minAccessTime(SSLTeam* team)
{
    SSLRobot* nr_rob = nearestPlayer(team);
    double min_acc_time = access_time[(int)team->color][nr_rob->id];
    return min_acc_time;
}

bool SSLAnalyzer::canNearestPlayerShoot(SSLTeam *team, SSLBall *ball)
{
    bool canShoot = false;
    SSLRobot* robot = nearestPlayer(team);
    if(robot == NULL){
        std::cerr << "Can not find Nearest Player!!!" << std::endl;
        return false;
    }
    Vector2D distVec = (ball->Position() - robot->Position().to2D());
    if( (distVec.lenght() < robot->physic.radius + ball->radius)
            && (abs(angleForRotate(robot, ball->Position())) < M_PI/6.0 ))
    {
        canShoot = true;
        std::cerr << "Robot" << robot->id << robot->colorStr() << "now can Kick" << std::endl;
    }
    return canShoot;
}

double SSLAnalyzer::angleForRotate(SSLRobot *robot, Vector2D interceptPoint)
{
    Vector2D dist = interceptPoint - robot->Position().to2D();
    double rot; // = toStandardRadian(robot->orien() - atan2(dist.y, dist.x));
    if(rot > M_PI)
        rot = M_PI - rot;
    std::cerr << "teta for robot"<< robot->id << "to rotate:" << rot * 180.0/M_PI << std::endl;
    return rot;
}
std::list<double> SSLAnalyzer::openAnglesToGoal(const Vector2D &point,
                                                Side targetGoalSide, list<SSLRobot *> defenders)
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

double SSLAnalyzer::totalOpenAngle(const Vector2D &point, Side targetGoalSide, list<SSLRobot*> defenders)
{
    std::list<double> open_angles = openAnglesToGoal(point, targetGoalSide, defenders);
    double totalAngle = 0;
    if(open_angles.size()%2 ==1) {
        std::cerr << "DANGEROUS ERROR IN CALCULATION OF OPEN ANGLES" << std::endl;
        return 0;
    }
    for( int i=0; i < open_angles.size() ; i+=2 ) {
//        totalAngle += open_angles[i+1] - open_angles[i];
    }

    std::cerr << "Total Angle to Goal Side" << targetGoalSide <<
                "is =" << (totalAngle/M_PI) * 180 << "degree" << std::endl;
    return totalAngle;
}



