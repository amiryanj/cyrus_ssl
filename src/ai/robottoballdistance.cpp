#include "robottoballdistance.h"

// pre declaration of static fields
const SSLBall* RobotDistTo::ball = NULL;
const SSLRobot* RobotDistTo::nearestRobotToBall = NULL;
const SSLRobot* RobotDistTo::nearestRobotToBallOfTeam[] = {NULL, NULL};
double RobotDistTo::minTimeToBall = INFINITY;
double RobotDistTo::minTimeToBallOfTeam[] = {INFINITY, INFINITY};

RobotDistTo::RobotDistTo(const SSLRobot *rob, const SSLBall *bal)
{
    this->robot = rob;
    this->ball = bal;
}

double RobotDistTo::getEuclideanTimeToBallSec() const
{
    return this->euclideanTimeB;
}

double RobotDistTo::getManifoldTimeToBallSec() const
{
    return this->onManifoldTimeB;
}

Vector2D RobotDistTo::getBallInstersectPoint() const
{
    return this->intersectPointB;
}

double RobotDistTo::distToPoint(SSLRobot *robot, const Vector2D &point)
{
    try {
        if(robot== NULL) {
            throw "Error: No Robot to compute euclidean distance";
        }

        Vector2D distVec = robot->Position().to2D() - ball->Position();
        double dist = distVec.lenght() / 1000.0;
        return dist / robot->physic.max_lin_vel_mmps;
    }
    catch (const char* msg) {
        std::cerr << "Exception: " << msg << std::endl;
        return INFINITY;
    }
}

void RobotDistTo::computeEuclideanToBall()
{
    try {
        if(RobotDistTo::ball == NULL) {
            throw "No ball found at the world";
        }
        if(this->robot== NULL) {
            throw "Error: No Robot to compute euclidean distance";
        }

        Vector2D dist = robot->Position().to2D() - ball->Position();
        this->euclideanDistB = dist.lenght() / 1000.0;
        this->euclideanTimeB = this->euclideanDistB / robot->physic.max_lin_vel_mmps;

        if(this->euclideanTimeB < minTimeToBallOfTeam[robot->color])
        {
            minTimeToBallOfTeam[robot->color] = this->euclideanTimeB;
            nearestRobotToBallOfTeam[robot->color] = this->robot;
        }

        if(this->euclideanTimeB < minTimeToBall)
        {
            minTimeToBall = this->euclideanTimeB;
            RobotDistTo::nearestRobotToBall = this->robot;
        }

    } catch (const char* msg) {
        std::cerr << "Exception: " << msg << std::endl;
    }
}

// this function uses binary search inorder to find a time interval
// in which the robot can access the ball
void RobotDistTo::computeManifoldToBall()
{
    // TO DO

//    double t_est = 0;
//    Vector2D intercept;
//    // time which robot can reach its max linear speed
//    double t_lim1 = (robot.physic.max_lin_vel - robot.Speed().lenght2D())
//                            /robot.physic.max_lin_acc;
//    double t_lim2 = (robot.physic.max_lin_vel + robot.Speed().lenght2D())
//                            /robot.physic.max_lin_acc;

//    for(double t_Low=0, t_High=4.0; ; ) // in sec
//    {
//        double t_range = t_High - t_Low;
//        Vector2D center0 = robot.Position().to2D() + robot.Speed().to2D() * t_High ;
//        Vector2D center1;
//        double forw_disp, backw_disp, radius;

//        if(t_High < t_lim1)
//        {
//            center1 = center0 ;
//            radius = t_High * t_High * robot.physic.max_lin_acc / 2.0;
//        }
//        else if(t_High < t_lim2)
//        {
//            forw_disp = robot.physic.max_lin_acc * (t_lim1 * t_lim1) / 2.0
//                    + robot.physic.max_lin_vel * (t_High - t_lim1) ;
//            backw_disp = robot.physic.max_lin_acc * (t_High * t_High ) / 2.0;
//            radius = (forw_disp + backw_disp)/2.0;
//            center1 = center0 + robot.Speed().normalized2D() * (forw_disp - backw_disp);
//        }
//        else
//        {
//            forw_disp = robot.physic.max_lin_acc * (t_lim1 * t_lim1) / 2.0
//                    + robot.physic.max_lin_vel * (t_High - t_lim1) ;
//            backw_disp = robot.physic.max_lin_acc * (t_lim2 * t_lim2 ) / 2.0
//                    + robot.physic.max_lin_vel * (t_High - t_lim2) ;
//            radius = (forw_disp + backw_disp)/2.0;
//            center1 = center0 + robot.Speed().normalized2D() * (forw_disp - backw_disp);
//        }

////        QRegion region(1000.0*(center1.x()-radius/2),1000.0*(center1.y()-radius/2),
////                               1000.0*2.0*radius, 1000.0*2.0* radius, QRegion::Ellipse);

////        Vector2D point = (1000.0*(ball.position + t_High * ball.speed).toPoint());
////        if(!region.contains(point))
//        if(!((ball.Position() + ball.Speed() * t_High - center1).lenght()
//                            <= radius + robot.physic.radius + ball.radius))

//             t_Low = t_High;

//        t_High = t_Low + t_range/2.0 ;
//        if((t_High - t_Low) < 2 * precison )  // precision = 1 ms
//        {
//            t_est = (t_High + t_Low)/2;
//            intercept = ball.Position() + ball.Speed() * t_est;
//            break;
//        }
//    }

//    return t_est;
}
