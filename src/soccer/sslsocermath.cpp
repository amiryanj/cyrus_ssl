#include "sslsocermath.h"


float SSLSocerMath::getFacingToPoint(const Vector2D& myPosition, const Vector2D& target)
{
    double deltaX = (target.X() - myPosition.X());
    double deltaY = (target.Y() - myPosition.Y());

    double facing = 0;

    if(deltaX > 0){
        facing = atan(deltaY / deltaX);
    }else if(deltaX < 0){
        facing = atan(deltaY / deltaX) + M_PI / (double)2;
    }else if(deltaY == 0){
        if(deltaX >= 0){
            facing = 0;
        }else{
            facing = -M_PI / (double)2;
        }
    }

    while(facing < 0){
        facing -= M_PI;
    }

    return (float) facing;
}

bool SSLSocerMath::isRobotOutsideOfDefenceArea(const Vector2D &, SSL::Side side)
{


}

bool SSLSocerMath::isRobotFacingToEnemy(float facing, Side enemySide)
{
    //???
    //is right side positive ?
    if(enemySide == SSL::Right){
        if((facing >= 0 && facing<= M_PI / (double)2)
                || (facing >= M_PI * (double)3 / (double)2 && facing<= M_PI * (double)2)){
            return true;
        }
    }else{
        if(!((facing >= 0 && facing<= M_PI / (double)2)
             || (facing >= M_PI * (double)3 / (double)2 && facing<= M_PI * (double)2))){
            return true;
        }
    }


    return false;

}

Vector2D SSLSocerMath::getGoalPosition(Side side)
{
    return Vector2D(0, side * (double) FIELD_LENGTH / 2.0);

}

Vector2D SSLSocerMath::getBlockPosition(Vector2D offenserPos, Vector2D blockedTargetPos, int numberofBlockers, int indexOfThisDefencer, float radius)
{



}

