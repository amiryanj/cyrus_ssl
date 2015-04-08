#include "testskills.h"
#include "../../common/math/vector3d.h"
#include "../paramater-manager/parametermanager.h"
#include "../ai/SSLGame.h"
#include "../soccer/sslskill.h"
#include "../soccer/sslgamepositions.h"
#include "../ai/SSLWorldModel.h"
#include "../definition/SSLBall.h"

TestSkills::TestSkills()
{
    target[0]= Vector3D(100 ,-2500,M_PI);
    target[1]= Vector3D(3000,-2500,M_PI/2);
    //target[2]= Vector3D(-2000,+1500,0);
 //   target[3]= Vector3D(-500,+1500,-M_PI/2);
    targetIndex=0;

    agent = SSLGame::getInstance()->getAgent(ParameterManager::getInstance()->
                                                       get<int>("skills.under_test_robot"));
}

void TestSkills::testGotoPoint()
{
    SSLGame::getInstance()->setEnabled(false);
    agent = SSLGame::getInstance()->getAgent(ParameterManager::getInstance()->
                                                       get<int>("skills.under_test_robot"));
    if( agent !=0 && !agent->isNull() )  {

        agent->skill->goToPoint(target[targetIndex]);

        //  agent->skill->consiceMove(agent->robot->Position(), target[i], SSLSkill::defaultTolerance);

        Vector3D diff = agent->robot->Position() - target[targetIndex];
        if(diff.lenght2D() < 50)
        {

            targetIndex = (targetIndex+1)%2;
        }
    }
}

void TestSkills::testGotoBallDefense()
{
    SSLGame::getInstance()->setEnabled(false);
    agent = SSLGame::getInstance()->getAgent(ParameterManager::getInstance()->
                                                       get<int>("skills.under_test_robot"));
    if( agent !=0 && !agent->isNull() )  {
        Vector3D target_ball_defense(SSL::Position::wallStandFrontBall(0,
                                                    world->mainBall()->Position()));

        agent->skill->goToPoint(target_ball_defense);
    }
}

void TestSkills::testKickBall()
{
    SSLGame::getInstance()->setEnabled(false);
    agent = SSLGame::getInstance()->getAgent(ParameterManager::getInstance()->
                                                       get<int>("skills.under_test_robot"));
    if( agent !=0 && !agent->isNull() )  {

        agent->skill->goAndKick(world->mainBall()->Position(), SSL::Position::opponentGoalCenter(), 1);

//        Vector3D target_ball_kick(SSL::Position::KickStylePosition( world->mainBall()->Position(),
//                                                                    SSL::Position::opponentGoalCenter(), 10));
//        agent->skill->goToPoint(target_ball_kick);
    }
}
