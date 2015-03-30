#include "testgotopoint.h"
#include "../../common/math/vector3d.h"
#include "../paramater-manager/parametermanager.h"
#include "../ai/SSLGame.h"
#include "../soccer/sslagent.h"
#include "../soccer/sslskill.h"
#include "paramater-manager/parametermanager.h"
TestGoToPoint::TestGoToPoint()
{
}

void TestGoToPoint::check()
{
    Vector3D target(200, 300, 0.0);
    SSLAgent* agent = SSLGame::getInstance()->getAgent(ParameterManager::getInstance()->
                                                       get<int>("general.test.robot_num"));

    if( agent !=0 && !agent->isNull() )  {
        agent->skill->goToPoint(target);
    }
}
