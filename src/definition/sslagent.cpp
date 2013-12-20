#include "sslagent.h"

SSLAgent::SSLAgent()
{
//    planner = new Planning::RRTPlanner();
    Planning::PlannerAgentShape agent(b2Shape::e_circle);
    agent.shape->m_radius = this->realRobot->physic.radius;
    planner.setAgent(agent);

    Planning::PlannerBound bound(-FIELD_LENGTH/2, -FIELD_WIDTH/2, FIELD_LENGTH/2 , FIELD_WIDTH/2);
    planner.setBound(bound);
}

SSLAgent::~SSLAgent()
{
//    if(this->planner)
//        delete planner;
}

bool SSLAgent::isNull()
{
    return !(this->realRobot->isInField);
}

int SSLAgent::getID() const
{
    if(this->realRobot == NULL)
    {
        std::cerr << "*** The Agent has NO ROBOT ***" << std::endl;
        return -1;
    }
    return this->realRobot->id;
}

void SSLAgent::run()
{
    if(this->role == NULL)
    {
        std::cerr << "*** The Agent has NO ROLE ***" << std::endl;
        return;
    }

    if(this->realRobot == NULL)
    {
        std::cerr << "*** The Agent has NO ROBOT Assigned ***" << std::endl;
        return;
    }

    this->role->run();

    planner.setInitial(this->realRobot->Position());
    planner.setGoalState(this->target);


}
