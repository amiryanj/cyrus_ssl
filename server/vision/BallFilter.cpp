#include "BallFilter.h"

#include "../ai/SSLWorldModel.h"
#include "../definition/SSLRobot.h"
#include "../definition/SSLBall.h"

#define EPS 1e-5

BallFilter::BallFilter()
{
    rawData.reserve(MAX_BALL_MEMORY + 1);
}

void BallFilter::putNewFrame(const Frame &fr)
{
    if(rawData.empty()) { // initial raw data when the first frame received
        for(int i=0; i< MAX_BALL_MEMORY; i++) {
            BallKinematic bk_;
            bk_.timeStamp_second = fr.timeStampMilliSec /1000.0 - (i *0.0166); // avoid dividing by zero
                                                                               // in following computations
            bk_.position = fr.position.to2D();
            bk_.displacement = Vector2D(0.0, 0.0);
            bk_.velocity = Vector2D(0.0, 0.0);
            bk_.acceleration = Vector2D(0.0, 0.0);
            rawData.insert(rawData.begin(), bk_);
        }
        m_filteredPosition = fr.position.to2D();
        m_displacement = Vector2D(0.0, 0.0);
        m_filteredVelocity = Vector2D(0.0, 0.0);
        m_accleration = Vector2D(0.0, 0.0);
    }

    else {
        assert( rawData.size() >= 2 );

        BallKinematic bk_;
        bk_.timeStamp_second = fr.timeStampMilliSec / 1000.0;
        bk_.position = fr.position.to2D();
        bk_.displacement = (bk_.position - getRawData(0).position);
        bk_.velocity = bk_.displacement / (bk_.timeStamp_second - getRawData(0).timeStamp_second);

        bk_.acceleration = (bk_.velocity - getRawData(0).velocity) /
                (bk_.timeStamp_second - getRawData(0).timeStamp_second);

        rawData.insert(rawData.begin(), bk_);
        rawData.pop_back();
    }

    if(getRawData(0).displacement.X() == 0)  {
        cout << "$$$$$$$$$$$ zero velocity $$$$$$$$$$" << endl;
        int dummy = 0;
        dummy ++;
    }


    assert( rawData.size() == MAX_BALL_MEMORY );
}

void BallFilter::putNewFrameWithManyBalls(vector<Frame> balls_)
{
    if(balls_.size() > 1)
        cout << "many balls on field" << endl;

    double min_dist = INFINITY;
    int min_index = -1;
    for(uint i=0; i<balls_.size(); i++) {
        double dist_i = (((Frame)balls_[i]).position.to2D() - m_filteredPosition).lenght();
        if(dist_i < min_dist) {
            min_dist = dist_i;
            min_index = i;
        }
    }
    if(min_index >0)
        this->putNewFrame(balls_[min_index]);
}

void BallFilter::runFilter()
{
    if(rawData.empty()) {
//        cerr << "No ball deteceted in the field" << endl;
        return;
    }
    // check for changing the ball state
    if(getBallStoppedState() == BALL_NOT_STOPPED) {
        SSLWorldModel::getInstance()->mainBall()->setStopped(BALL_NOT_STOPPED);
    }

    m_rawPosition  = getRawData(0).position;
    m_displacement = getRawData(0).displacement;
    m_rawVelocity  = getRawData(0).velocity;

    m_filteredPosition = getRawData(0).position;
    m_filteredVelocity = getRawData(0).velocity;
    m_accleration      = getRawData(0).acceleration;

    if( SSLWorldModel::getInstance()->mainBall()->isStopped() ) {
        m_filteredVelocity = Vector2D(0, 0);
//    } else {
    }

    double disp_error_ = m_accleration.lenght(); // / m_filteredVelocity.lenght();
    double turn_error_ = m_accleration.arctan();

    double last_delta_t_sec = getRawData(0).timeStamp_second - getRawData(1).timeStamp_second;

    naiveFilter.predict(last_delta_t_sec);
    naiveFilter.m_alfa = 0.1 + 0.5 * exp( -0.000005 * disp_error_);
    naiveFilter.m_beta = (0.1 + 0.5 * exp( -0.01 * turn_error_))
                        *(0.1 + 0.6 * exp( -0.000005 * disp_error_));
    naiveFilter.observe(getRawData(0).position.to3D(),
                        getRawData(0).velocity.to3D(),
                        getRawData(0).acceleration.to3D());

    FilterState fs = naiveFilter.filter();
    this->m_filteredPosition = fs.pos.to2D();
    this->m_filteredVelocity = fs.vel.to2D();

//    this->m_accleration = fs.acc.to2D();
}

Vector2D BallFilter::getUnfilteredSpeed() const
{
    return m_rawVelocity;
}

Vector2D BallFilter::getFilteredSpeed() const
{
    return m_filteredVelocity;
}

Vector2D BallFilter::getFilteredPosition() const
{
    return m_filteredPosition;
}

Vector2D BallFilter::getAcceleration() const
{
    return m_accleration;
}

Vector2D BallFilter::getDisplacement() const
{
    return m_displacement;
}

bool BallFilter::getBallStoppedState()
{
    if(SSLWorldModel::getInstance()->mainBall()->isStopped()) {
        vector<SSLRobot *> all_robots = SSLWorldModel::getInstance()->all_inFields();
        double minimum_distance = INFINITY;
        for(uint i=0; i<all_robots.size(); i++) {
            double dist_i = (((SSLRobot*)(all_robots.at(i)))->Position().to2D() - getFilteredPosition()).lenght();
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
    }
}
