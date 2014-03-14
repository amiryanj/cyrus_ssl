#include "sslagent.h"
#include "../ai/SSLGame.h"
#include "../transmitter/RobotCommandPacket.h"
#include "../transmitter/commandtransmitter.h"

using namespace std;

SSLAgent::SSLAgent(Color our_color, Side our_side)
{    
    this->role = NULL;
    this->robot = NULL;

    // initialize planner
    FieldBound bound;
    bound.set(-1.1 * FIELD_LENGTH/2, 1.1 * FIELD_LENGTH/2,
              -1.1 * FIELD_WIDTH/2, 1.1 * FIELD_WIDTH/2 );
    planner.setBound(bound);
    PlanningAgent plan_agent;
    plan_agent.setRadius(90); // in milimeter
    plan_agent.mass = 3.0; // kilo gram
    plan_agent.velocity_limit.set(3000, 3000, M_PI * 1.2);
    planner.setPlanningAgent(plan_agent);

    // initializing field obstacles for agent
    // ****************************************************************************************
    penaltyAreaObs.reserve(5);
    int z = (int) our_side;
    Obstacle* myPenaltyArea_C = new Obstacle(Obstacle::Field, b2Vec2(z* FIELD_LENGTH/2, 0),
                                                    FIELD_PENALTY_AREA_RADIUS * 0.9, 0);
    Obstacle* myPenaltyArea_T = new Obstacle(Obstacle::Field, b2Vec2(z* FIELD_LENGTH/2, FIELD_PENALTY_AREA_WIDTH/2),
                                                    FIELD_PENALTY_AREA_RADIUS * 0.9, 0);
    Obstacle* myPenaltyArea_D = new Obstacle(Obstacle::Field, b2Vec2(z* FIELD_LENGTH/2, -FIELD_PENALTY_AREA_WIDTH/2),
                                                    FIELD_PENALTY_AREA_RADIUS * 0.9, 0);
//    Obstacle* myPenaltyArea_C = new Obstacle(b2Vec2(z* FIELD_LENGTH/2, 0),
//                                                    FIELD_PENALTY_AREA_RADIUS*2 * .9, FIELD_PENALTY_AREA_WIDTH, 0);
    Obstacle* outFieldArea_R = new Obstacle(Obstacle::Field, b2Vec2(FIELD_LENGTH/2+300, 0),
                                                    150*2 ,  FIELD_WIDTH, 0);
    Obstacle* outFieldArea_L = new Obstacle(Obstacle::Field, b2Vec2(-FIELD_LENGTH/2-300, 0),
                                                    150*2 ,  FIELD_WIDTH, 0);
    penaltyAreaObs.push_back(myPenaltyArea_C);
    penaltyAreaObs.push_back(myPenaltyArea_T);
    penaltyAreaObs.push_back(myPenaltyArea_D);

    penaltyAreaObs.push_back(outFieldArea_L);
    penaltyAreaObs.push_back(outFieldArea_R);

    allRobotsObs.reserve(MAX_ID_NUM * 2);
    for(unsigned int i=0; i< MAX_ID_NUM *2; i++) {
        Obstacle* ob_ = new Obstacle(Obstacle::Robot, b2Vec2(0, 0), ROBOT_RADIUS, 0);
        allRobotsObs.push_back(ob_);
    }

    ballOb = new Obstacle(Obstacle::Ball, b2Vec2(0,0), BALL_RADIUS, 0);
    // ****************************************************************************************

    // initialize controller
    // ********************************************************
    controller.setParameters(0.5, 0.0, 0.01);
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
            return; // ************ comment this line ***************
            throw "role of agent is null";
        }
        if(this->robot == NULL)
            throw "Agent has NO ROBOT Assigned";
        this->target = this->role->run();
        // run the planner
        Station init_state;
        init_state.setPosition(this->robot->Position());
        init_state.setVelocity(this->robot->Speed());

        if(init_state.position.X() == INFINITY || init_state.position.X() == NAN)
            return;
        planner.setInitialState(init_state);
        planner.setGoalRegion(this->target);

        ObstacleSet tmpAllObstacles;
        tmpAllObstacles.reserve(2*MAX_ID_NUM + 6);
        if(this->role->type != SSLRole::GoalKeeper) {
            tmpAllObstacles.insert(tmpAllObstacles.begin(), penaltyAreaObs.begin(), penaltyAreaObs.end());
        }

        // update position of dynamic obstacles
        vector<SSLRobot*> all_actual_robots = SSLWorldModel::getInstance()->allRobots();
        for(unsigned int i=0; i<allRobotsObs.size(); i++)
        {
            Obstacle* ob_  = allRobotsObs.at(i);
            SSLRobot* rob_ = all_actual_robots.at(i);
//            b2Vec2 pos;
            if(rob_->color == this->robot->color && rob_->id == this->getID())
                continue;
            if(rob_->isInField) {
                ob_->m_transform.Set(Vector2D(rob_->Position().X(), rob_->Position().Y()).b2vec2(), rob_->Position().Teta());
                tmpAllObstacles.push_back(ob_);
            }
        }

        SSLBall* actual_ball = SSLWorldModel::getInstance()->mainBall();
        ballOb->m_transform.Set(b2Vec2(actual_ball->Position().X(), actual_ball->Position().Y()), 0);

        // we treat dynamic and static obstacles in the same way
//        if(/* the robot should consider ball as obstacle*/)
        tmpAllObstacles.push_back(ballOb);

        planner.setStaticObstacles(tmpAllObstacles);

        planner.solve();
//        assert(planner.planningResult == true); // this assumption is not true
//        PotentialFieldSolve();
//        if(!planner.planningResult)
//            planner.GRRTsolve();

        temp_desired_vel = planner.getControl(0);
//        double speed = .7;
//        speed *= this->robot->physic.max_lin_vel_mmps;
//        temp_desired_vel.normalize2D();
//        temp_desired_vel *= speed;
//        controller.setPoint(temp_desired_vel, this->robot->Speed());

//        temp_applied_vel_global = controller.getControl();
        temp_applied_vel_global = temp_desired_vel; // because controller is not working yet

//        temp_applied_vel_local.set(1000, 0, 0);
//        temp_applied_vel.rotate(M_PI_4l);
        temp_applied_vel_local = temp_applied_vel_global;
        temp_applied_vel_local.rotate(-robot->orien());

//        temp_applied_vel_local.setTeta(0);
//        temp_applied_vel_local.normalize2D();
//        temp_applied_vel_local *= .6;

        cout << "Desired vel for robot #" << this->getID() << " is: X= " << temp_desired_vel.X()
             << " Y= " << temp_desired_vel.Y() << " teta=" << temp_desired_vel.Teta() << endl;

        cout << "Applied vel for robot #" << this->getID()
             << " is: V_x= " << temp_applied_vel_local.X()
             << " V_y= " << temp_applied_vel_local.Y()
             << " ,V angle = " << temp_applied_vel_local.to2D().arctan()
             << " ,speed = " << temp_applied_vel_local.lenght2D()
             << " omega=" << temp_applied_vel_local.Teta() << endl;

        RobotCommandPacket pkt;

        pkt.setVelocityByWheels(temp_applied_vel_local.X(), temp_applied_vel_local.Y(), temp_applied_vel_local.Teta());
        CommandTransmitter::getInstance()->send(this->getID(), pkt);

    }

    catch(const char* msg) {
        cerr << "Exception: SSLAgent :" << msg << endl;
    }

}
