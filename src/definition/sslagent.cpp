#include "sslagent.h"
#include "../ai/SSLGame.h"
#include "../transmitter/RobotCommandPacket.h"
#include "../transmitter/commandtransmitter.h"

using namespace std;

SSLAgent::SSLAgent(Color color)
{    
    this->role = NULL;
    this->robot = NULL;
    // initialize planner
    FieldBound bound;
    bound.set(-1.2 * FIELD_LENGTH/2, 1.2 * FIELD_LENGTH/2,
              -1.2 * FIELD_WIDTH/2, 1.2 * FIELD_WIDTH/2 );
    planner.setBound(bound);
    PlanningAgent plan_agent;
    plan_agent.setRadius(90); // in milimeter
    plan_agent.mass = 3.0; // kilo gram
    plan_agent.velocity_limit.set(3, 3, 2);
    planner.setPlanningAgent(plan_agent);

    penaltyAreaObstacleSet.reserve(3);
    int z = (int) color;
    Obstacle* myPenaltyArea_1 = new Obstacle(b2Vec2(z* FIELD_LENGTH/2, FIELD_PENALTY_AREA_WIDTH/2),
                                                    FIELD_PENALTY_AREA_RADIUS, 0);
    Obstacle* myPenaltyArea_2 = new Obstacle(b2Vec2(z* FIELD_LENGTH/2, -FIELD_PENALTY_AREA_WIDTH/2),
                                                    FIELD_PENALTY_AREA_RADIUS, 0);
    Obstacle* myPenaltyArea_3 = new Obstacle(b2Vec2(z* FIELD_LENGTH/2, 0),
                                                    FIELD_PENALTY_AREA_RADIUS*2, FIELD_PENALTY_AREA_WIDTH, 0);

    penaltyAreaObstacleSet.push_back(myPenaltyArea_1);
    penaltyAreaObstacleSet.push_back(myPenaltyArea_2);
    penaltyAreaObstacleSet.push_back(myPenaltyArea_3);

    myDynamicObstacleSet.reserve((MAX_ID_NUM+1) *2);
    for(unsigned int i=0; i< (MAX_ID_NUM+1) *2; i++) //
    {
        Obstacle* ob_ = new Obstacle(b2Vec2(0, 0), ROBOT_RADIUS, 0);
        myDynamicObstacleSet.push_back(ob_);
    }

    cout << "toop ra niz bayad be mavane ezafe kard" << endl;

}

SSLAgent::~SSLAgent()
{
}

bool SSLAgent::isNull()
{
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
        if(this->role == NULL)
            throw "role of agent is null";
        if(this->robot == NULL)
            throw "Agent has NO ROBOT Assigned";
        this->target = this->role->run();
        // run the planner
        Station init_state;
        init_state.setPosition(this->robot->Position());
        init_state.setVelocity(this->robot->Speed());

        planner.setInitialState(init_state);
        planner.setGoalRegion(this->target);
        for(int i=0; i<myDynamicObstacleSet.size(); i++)
        {
            Obstacle* ob_  = myDynamicObstacleSet.at(i);
            SSLRobot* rob_ = SSLWorldModel::getInstance()->allRobotsExcept(this->robot).at(i);
            ob_->transform.Set(b2Vec2(rob_->Position().X(), rob_->Position().Y()), rob_->Position().Teta());
        }

        planner.setDynamicObstacles(myDynamicObstacleSet);
        if(this->role->type != SSLRole::ROLE_GOALIE)
        {
            planner.setStaticObstacles(penaltyAreaObstacleSet);
        }

        planner.RRTsolve();
        Vector3D desiredVelocity = planner.getControl(0);
        RobotCommandPacket p;
        p.setVelocity(desiredVelocity);
        CommandTransmitter::getInstance()->send(this->getID(), p);

        // TODO
        // run the controller

    }

    catch(const char* msg) {
        cerr << "Exception: SSLAgent :" << msg << endl;
    }

}
