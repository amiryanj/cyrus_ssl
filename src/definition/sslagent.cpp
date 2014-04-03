#include "sslagent.h"
#include "../ai/SSLGame.h"
#include "../transmitter/RobotCommandPacket.h"
#include "../transmitter/commandtransmitter.h"
#include "../soccer/roles/sslrole.h"

using namespace std;

SSLAgent::SSLAgent()
{    
    this->role = NULL;
    this->robot = NULL;

    // initialize planner
    FieldBound bound;
    bound.set(-1.1 * FIELD_LENGTH/2, 1.1 * FIELD_LENGTH/2,
              -1.1 * FIELD_WIDTH/2, 1.1 * FIELD_WIDTH/2 );
    planner.setBound(bound);
    PlanningAgent plan_agent;
    plan_agent.setRadius(ROBOT_RADIUS); // in milimeter
    plan_agent.mass = 3.0; // kilo gram
    plan_agent.velocity_limit.set(3000, 3000, M_PI * 1.2);
    planner.setPlanningAgent(plan_agent);

    // initialize controller
    // ********************************************************
    controller.setParameters(0.2, 0.0, 0.0);
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
        cerr << "Exception: SSLAgent :" << msg << endl;
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
        else
            role->run();
    }

    catch(const char* msg) {
        cerr << "Exception: SSLAgent :" << msg << endl;
    }

}
