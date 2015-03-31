#include "testgotopoint.h"
#include "../../common/math/vector3d.h"
#include "../paramater-manager/parametermanager.h"
#include "../ai/SSLGame.h"
#include "../soccer/sslagent.h"
#include "../soccer/sslskill.h"
#include "paramater-manager/parametermanager.h"
TestGoToPoint::TestGoToPoint()
{
    target[0]= Vector3D(-500,-1500,M_PI);
    target[1]= Vector3D(-2000,-1500,M_PI/2);
    target[2]= Vector3D(-2000,+1500,0);
    target[3]= Vector3D(-500,+1500,-M_PI/2);
    i=0;
}

void TestGoToPoint::check()
{

    SSLAgent* agent = SSLGame::getInstance()->getAgent(ParameterManager::getInstance()->
                                                       get<int>("general.test.robot_num"));

    if( agent !=0 && !agent->isNull() )  {
        agent->skill->goToPoint(target[i]);
        Vector3D diff = agent->robot->Position() - target[i];
        if(diff.lenght2D() < 100)
        {

            i=(i+1)%4;
        }
    }

}
