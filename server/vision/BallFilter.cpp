#include "BallFilter.h"

#include "../ai/SSLWorldModel.h"
#include "../definition/SSLRobot.h"
#include "../definition/SSLBall.h"
#include "../paramater-manager/parametermanager.h"
#include "../../common/math/sslmath.h"

#define EPS 1e-5

BallFilter::BallFilter()
{
    rawData.reserve(MAX_BALL_MEMORY + 1);
}

void BallFilter::initialize(const SSLFrame &first_frame)
{
    if(rawData.empty())  { // initial raw data when the first frame received
        for(int i=0; i< MAX_BALL_MEMORY; i++) {
            BallKinematic bk_;
            bk_.timeStamp_second = first_frame.timeStampMilliSec /1000.0 - (i *0.0166); // avoid dividing by zero
                                                                               // in following computations
            bk_.position = first_frame.position.to2D();
            bk_.displacement = Vector2D(0.0, 0.0);
            bk_.velocity = Vector2D(0.0, 0.0);
            bk_.acceleration = Vector2D(0.0, 0.0);
            rawData.insert(rawData.begin(), bk_);
        }
        m_filteredPosition = first_frame.position.to2D();
        m_displacement = Vector2D(0.0, 0.0);
        m_filteredVelocity = Vector2D(0.0, 0.0);
        m_acceleration = Vector2D(0.0, 0.0);
    }
}

void BallFilter::putNewFrame(const SSLFrame &detected_ball)
{
    BallKinematic bk_;
    bk_.timeStamp_second = detected_ball.timeStampMilliSec / 1000.0;
    bk_.position = detected_ball.position.to2D();
    bk_.displacement = (bk_.position - getRawData(0).position);
    bk_.velocity = bk_.displacement / (bk_.timeStamp_second - getRawData(0).timeStamp_second);

    bk_.acceleration = (bk_.velocity - getRawData(0).velocity) /
            (bk_.timeStamp_second - getRawData(0).timeStamp_second);

    rawData.insert(rawData.begin(), bk_);
    rawData.pop_back();
}

void BallFilter::putNewFrameWithManyBalls(vector<SSLFrame> detected_balls)
{
    if(detected_balls.size() > 1)
        cout << "many balls on field" << endl;

    double min_dist = INFINITY;
    int min_index = -1;
    for(uint i=0; i<detected_balls.size(); i++) {
        double dist_i = (((SSLFrame)detected_balls[i]).position.to2D() - m_filteredPosition).lenght();
        if(dist_i < min_dist) {
            min_dist = dist_i;
            min_index = i;
        }
    }

    if( min_index > 0 )
        this->putNewFrame(detected_balls[min_index]);
}

void BallFilter::run()
{
    if( rawData.empty() ) {
//        cerr << "No ball deteceted in the field" << endl;
        return;
    }
    // check for changing the ball state

    m_rawPosition  = getRawData(0).position;
    m_displacement = getRawData(0).displacement;
    m_rawVelocity  = getRawData(0).velocity;

    m_acceleration     = getRawData(0).acceleration;
//    m_filteredPosition = getRawData(0).position;
//    m_filteredVelocity = getRawData(0).velocity;

    bool isBallStopped = getBallStoppedState();
    SSLWorldModel::getInstance()->mainBall()->setStopped(isBallStopped);

    if( isBallStopped ) {
        m_filteredVelocity = Vector2D(0, 0);
        return;
    //  } else   {
    }

    double disp_error_ = m_acceleration.lenght(); // / m_filteredVelocity.lenght();
    disp_error_ = log10(disp_error_) /7.0;


    double turn_error_ = m_acceleration.arctan();

    double last_delta_t_sec = getRawData(0).timeStamp_second - getRawData(1).timeStamp_second;

    alphaBetaFilter.predict(last_delta_t_sec);
    alphaBetaFilter.m_alfa = SSL::bound(1.0 - disp_error_, 0.1, 0.8);
    alphaBetaFilter.m_beta = SSL::sigmoid(turn_error_ / M_PI_4 , 0.1, 0.3 );

    alphaBetaFilter.observe(getRawData(0).position.to3D(),
                        getRawData(0).velocity.to3D(),
                        getRawData(0).acceleration.to3D());

    SSLObjectState filter_result = alphaBetaFilter.filter();
    this->m_filteredPosition = filter_result.pos.to2D();
    this->m_filteredVelocity = filter_result.vel.to2D();

   ParameterManager* pm = ParameterManager::getInstance();
   SSLObjectState predict_result = alphaBetaFilter.predict(0.001 * pm->get<double>("kalman.vision_delay_ms"));
   this->m_filteredPosition = predict_result.pos.to2D();
}

bool BallFilter::isEmpty() const
{
    return rawData.empty();
}

bool BallFilter::getBallStoppedState()
{
    if(SSLWorldModel::getInstance()->mainBall()->isStopped()) {
        vector<SSLRobot *> all_robots = SSLWorldModel::getInstance()->all_inFields();
        double minimum_distance = INFINITY;
        for(uint i=0; i<all_robots.size(); i++) {
            double dist_i = (((SSLRobot*)(all_robots.at(i)))->Position().to2D() - m_filteredPosition).lenght();
            dist_i -= SSLWorldModel::getInstance()->mainBall()->m_radius - ((SSLRobot*)(all_robots.at(i)))->m_radius;
            minimum_distance = min(dist_i, minimum_distance);
        }

        double totoal_rotation_5_frame = getRawData(0).turnInDegree() +
                                         getRawData(1).turnInDegree() +
                                         getRawData(2).turnInDegree() ;

        if(minimum_distance < 30) { // there is very close robot
            if( totoal_rotation_5_frame < 50 )
                return false;
        }

        int large_displacement_counter = (getRawData(0).displacement.lenght() > 15) +
                                         (getRawData(1).displacement.lenght() > 15) +
                                         (getRawData(2).displacement.lenght() > 15) +
                                         (getRawData(3).displacement.lenght() > 15) +
                                         (getRawData(4).displacement.lenght() > 15);

        if(minimum_distance < 100) { // there is some robot around ball
            if((totoal_rotation_5_frame < 50) && large_displacement_counter >= 3)
                return false;
        } else { // no robot around ball
            double total_displacement = (getRawData(0).position - getRawData(5).position).lenght();
            if((large_displacement_counter >= 4) && (total_displacement > 50))
                return false;
        }

        return true; // observation says that ball is still stopped
    } else {
        // we dont consider the moments where ball get stopped during a game
        // set stop is just called by referee signals
        return false;
    }

}
