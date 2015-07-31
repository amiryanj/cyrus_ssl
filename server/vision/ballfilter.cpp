#include "ballfilter.h"

#include "../ai/SSLWorldModel.h"
#include "../definition/SSLRobot.h"
#include "../definition/SSLBall.h"
#include "../paramater-manager/parametermanager.h"
#include "../../shared/utility/generalmath.h"
#include "../log-tools/networkplotter.h"

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
using namespace boost;

#define EPS 1e-5

BallFilter::BallFilter()
{
    rawData.reserve(MAX_BALL_MEMORY + 1);
}

void BallFilter::initialize(const OneObjectFrame &initial_frame)
{
    float default_fps = ParameterManager::getInstance()->get<float>("vision.default_frame_per_second");

    if(rawData.empty())  { // initial raw data when the first frame received
        for(int i=0; i< MAX_BALL_MEMORY; i++)  {
            SSLBallState ball_;
            ball_.camera_id = initial_frame.camera_id;
            ball_.timeStamp_second = initial_frame.timeStampMSec /1000.0 - (i / default_fps); // avoid dividing by zero
                                                                               // in following computations
            ball_.position = initial_frame.position.to2D();
            ball_.displacement = Vector2D(0.0, 0.0);
            ball_.velocity = Vector2D(0.0, 0.0);
            ball_.acceleration = Vector2D(0.0, 0.0);
            rawData.insert(rawData.begin(), ball_);
        }
        m_filteredPosition = initial_frame.position.to2D();
        m_displacement = Vector2D(0.0, 0.0);
        m_filteredVelocity = Vector2D(0.0, 0.0);
        m_acceleration = Vector2D(0.0, 0.0);
    }
}

void BallFilter::putNewFrame(const OneObjectFrame &detected_ball)
{
    hasUnprocessedData = true;

    // drop the balls in a new camera while the capture time
    // of last detected ball is not past more than 10 ms
    float default_fps = ParameterManager::getInstance()->get<float>("vision.default_frame_per_second");
    if( ( detected_ball.camera_id != getRawData(0).camera_id)
      && (detected_ball.timeStampMSec/1000.0 - getRawData(0).timeStamp_second) < (0.6 * 1/default_fps))
    {
        return;
    }

    SSLBallState ball_;
    ball_.timeStamp_second = detected_ball.timeStampMSec / 1000.0;
    ball_.camera_id        = detected_ball.camera_id;
    ball_.position         = detected_ball.position.to2D();
    ball_.displacement     = (ball_.position - getRawData(0).position);
    ball_.velocity         = ball_.displacement / (ball_.timeStamp_second - getRawData(0).timeStamp_second);

    ball_.acceleration     = (ball_.velocity - getRawData(0).velocity) /
                              (ball_.timeStamp_second - getRawData(0).timeStamp_second);

    rawData.insert(rawData.begin(), ball_);

    NetworkPlotter::getInstance()->buildAndSendPacket("Raw Ball Speed", ball_.velocity.lenght());

    m_rawPosition  = getRawData(0).position;
    m_displacement = getRawData(0).displacement;
    m_rawVelocity  = getRawData(0).velocity;
    m_acceleration = getRawData(0).acceleration;

    // we are sure that raw data array size always remains constant
    rawData.pop_back();
}

void BallFilter::putNewFrameWithManyBalls(vector<OneObjectFrame> detected_balls)
{
    double min_dist = INFINITY;
    int min_index = -1;
    for(uint i=0; i<detected_balls.size(); i++) {
        double dist_i = (((OneObjectFrame)detected_balls[i]).position.to2D() - m_filteredPosition).lenght();
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
    if(!hasUnprocessedData) {
        return;
    }
    hasUnprocessedData = false;

    if( rawData.empty() ) {
        SSLWorldModel::getInstance()->mainBall()->setStopped(true);
        cerr << "Ball Filter is not initialized." << endl;
        return;
    }

    executeClusterFilter();

    // check for changing the ball state
    bool isBallStopped = getBallStoppedState();
    SSLWorldModel::getInstance()->mainBall()->setStopped(isBallStopped);

    if( isBallStopped )   {
        m_filteredVelocity = Vector2D(0, 0);
         accumulators::accumulator_set<double, accumulators::features<accumulators::tag::mean, accumulators::tag::variance> > acc_x;
         accumulators::accumulator_set<double, accumulators::features<accumulators::tag::mean, accumulators::tag::variance> > acc_y;
        for(int i=0; i<rawData.size(); i++) {
            acc_x( getRawData(i).position.X() );
            acc_y( getRawData(i).position.Y() );
        }
        m_filteredPosition.set(accumulators::mean(acc_x),  accumulators::mean(acc_y));
        return;
    }

    executeAlphaBetaFilter();
    m_filteredVelocity = m_clusteredVelocity;

    ParameterManager* pm = ParameterManager::getInstance();
    float vision_delay = pm->get<double>("vision.vision_delay_ms") * 0.001;
//    SSLObjectState predict_result = alphaBetaFilter.predict(vision_delay);
//    this->m_filteredPosition = predict_result.pos.to2D();
    this->m_filteredPosition = alphaBetaFilter.m_state.pos.to2D() + m_filteredVelocity * vision_delay;
}

void BallFilter::executeAlphaBetaFilter()
{
    double disp_error_ = m_acceleration.lenght(); // / m_filteredVelocity.lenght();
    disp_error_ = log10(disp_error_+1) /7.0;

//    NetworkPlotter::getInstance()->buildAndSendPacket("ball acceleration", disp_error_);

    double turn_error_ = m_acceleration.arctan();

    double last_delta_t_sec = getRawData(0).timeStamp_second - getRawData(1).timeStamp_second;


    alphaBetaFilter.predict(last_delta_t_sec);
    alphaBetaFilter.m_alfa = bound(1.0 - disp_error_, 0.1, 0.4);
    alphaBetaFilter.m_beta = sigmoid(turn_error_ / M_PI_4 , 0.1, 0.3 );

    if(m_rawVelocity.lenght() < 10000)
    {
        alphaBetaFilter.observe(getRawData(0).position.to3D(),
                                getRawData(0).velocity.to3D(),
                                getRawData(0).acceleration.to3D() );
    }

    SSLObjectState filter_result = alphaBetaFilter.filter();
    this->m_filteredPosition = filter_result.pos.to2D();
    this->m_filteredVelocity = filter_result.vel.to2D();   

    NetworkPlotter::getInstance()->buildAndSendPacket("ball speed", m_filteredVelocity.lenght());
}

void BallFilter::executeClusterFilter()
{
    uint clusterSize = 4;
    const float dataCoefficient[] = { 1.00, 0.80, 0.65,
                                      0.50, 0.43, 0.37, 0.33 }; // sum = 1.0
    vector<Vector2D> clusterData;
    uint raw_data_index = 0;
    float sum_coeff = 0;
    while(clusterData.size() < clusterSize)  {
        if(getRawData(raw_data_index).velocity.lenght() < 15000)  {
            clusterData.push_back(getRawData(raw_data_index).velocity);
        }
        raw_data_index ++;
        if(raw_data_index >= rawData.size())
            break;
    }

    Vector2D clusterMean;

    for(int i=0; i<3; i++)   {
        clusterMean.setZero();
        for ( int i=0; i<clusterSize; i++ )   {
            clusterMean += clusterData[i] * dataCoefficient[i];
            sum_coeff += dataCoefficient[i];
        }
        clusterMean = clusterMean / sum_coeff;
        float max_err = 0;
        short max_index = -1;
        for(int j=0; j<clusterData.size(); j++) {
            float err_j = ( clusterData[j] - clusterMean ).lenght();
            if(err_j >= max_err) {
                max_err = err_j;
                max_index = j;
            }
        }
        if( max_index < 0 )
            break;
        if((max_err) > 500*pow(2.0, i))   {
            clusterData.erase( clusterData.begin() + max_index );
        }
        else {
            break;
        }
    }

    clusterSize = clusterData.size();
    clusterMean.setZero();
    for ( int i=0; i<clusterSize; i++ )   {
        clusterMean += clusterData[i] / clusterSize;
    }
    m_clusteredVelocity = clusterMean;
}

bool BallFilter::isEmpty() const
{
    return rawData.empty();
}

bool BallFilter::getBallStoppedState()
{
    if(SSLWorldModel::getInstance()->mainBall()->isStopped()) {
        vector<SSLRobot *> all_robots = SSLWorldModel::getInstance()->getInFieldRobots();
        double minimum_distance = INFINITY;
        for(uint i=0; i<all_robots.size(); i++) {
            double dist_i = (((SSLRobot*)(all_robots.at(i)))->Position().to2D() - m_filteredPosition).lenght();
            dist_i -= SSLWorldModel::getInstance()->mainBall()->m_radius - ((SSLRobot*)(all_robots.at(i)))->m_radius;
            minimum_distance = std::min(dist_i, minimum_distance);
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
