#include "sslagent.h"
#include "../ai/SSLGame.h"
#include "../transmitter/RobotCommandPacket.h"
#include "../transmitter/commandtransmitter.h"
#include "../soccer/sslrole.h"

using namespace std;

SSLAgent::SSLAgent()
{    
    this->role = NULL;
    this->robot = NULL;
    this->skill = new SSLSkill(this);

    // initialize controller
    // ********************************************************
//    controller.setParameters(0.1, 0.04, 0.0);
    // ********************************************************
}

SSLAgent::~SSLAgent()
{
}

bool SSLAgent::isNull()
{
    if(robot == NULL)
        return true;
    return !(this->robot->isInField);
}

int SSLAgent::getID() const
{
    try {
        if(this->robot == NULL)
            throw "Agent hs no Robot";
        return this->robot->id;
    }
    catch(const char* msg) {
//        cerr << "Exception: SSLAgent :" << msg << endl;
        return -1;
    }
}

void SSLAgent::run()
{
    try {
        if(this->role == NULL) {
            return;
            throw "role of agent is null";
        }
        if(this->robot == NULL)
            throw "Agent has NO ROBOT Assigned";
        if(world->m_refereeState == SSLReferee::Halt) {
            role->Halt();
            throw "Agent in HALT State ";
        }
        else {
            skill->updateObstacles();
            role->run();
        }
    }

    catch(const char* msg) {
//        cerr << "Exception: SSLAgent :" << msg << endl;
    }

}
