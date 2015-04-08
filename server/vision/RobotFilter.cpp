#include "RobotFilter.h"
#include "../../common/math/sslmath.h"
#include "../paramater-manager/parametermanager.h"

using namespace std;

#define EPS 1e-5

RobotFilter::RobotFilter()
{    
    last_update_time_msec = 0;

    rawData.reserve(MAX_RAW_DATA_MEMORY + 1);
    // rawSpeedList is set to zero by default
    __medianFilterIndex = 0;

}

// insert new frame in the list and remove expired frames
void RobotFilter::putNewFrame(const SSLFrame &fr)
{

    // drop the balls in a new camera while the capture time
    // of last detected ball is not past more than 10 ms
    float default_fps = ParameterManager::getInstance()->get<float>("vision.default_frame_per_second");
    if( ( fr.camera_id != getRawData(0).camera_id)
      && (fr.timeStampMilliSec/1000.0 - getRawData(0).timeStamp_second) < (0.6 * 1/default_fps))
    {
        return;
    }

    hasUnprocessedData = true;
    last_update_time_msec = SSL::currentTimeMSec();

    SSLRobotState robot_;
    robot_.timeStamp_second = fr.timeStampMilliSec / 1000.0;
    robot_.camera_id = fr.camera_id;
    robot_.position  = fr.position;
    if( !rawData.empty() ) {
        robot_.position.setTeta(continuousRadian(robot_.position.Teta(), getRawData(0).position.Teta()-M_PI));
        robot_.displacement = (robot_.position - getRawData(0).position);
        robot_.velocity     = robot_.displacement / (robot_.timeStamp_second - getRawData(0).timeStamp_second);

        robot_.acceleration = (robot_.velocity - getRawData(0).velocity) /
                              (robot_.timeStamp_second - getRawData(0).timeStamp_second);
    }

    rawData.insert(rawData.begin(), robot_);

    if(rawData.size() > MAX_RAW_DATA_MEMORY)
        rawData.pop_back();
}

bool RobotFilter::isEmpty()
{
    return rawData.empty();
}

bool RobotFilter::isOnField()
{
    return (rawData.size() >= 3);
}

void RobotFilter::run()
{
    // removing decayed frames
    if((SSL::currentTimeMSec() - last_update_time_msec) > 15000.0) {
        rawData.clear();
    }

    if(!hasUnprocessedData) {
        return;
    }
    hasUnprocessedData = false;

    if( rawData.size() < 2 )
        return;


    int clusterSize = 6;
    const float dataCoefficient[] = { 0.19, 0.18, 0.17,
                                      0.13, 0.12, 0.11, 0.10 }; // sum = 1.0
    vector<SSLRobotState> clusterData;
    int raw_data_index = 0;
    while(clusterData.size() < clusterSize)  {
        if(getRawData(raw_data_index).velocity.lenght2D() < 6000)  {
            clusterData.push_back(getRawData(raw_data_index));
        }
        raw_data_index ++;
        if(raw_data_index >= rawData.size())
            break;
    }

    Vector3D meanVelocity;
    for ( int i=0; i<clusterSize; i++ )   {
        meanVelocity += ((SSLRobotState)clusterData[i]).velocity * dataCoefficient[i];
    }

    vector<float> dataErrors;
    for ( int i=0; i<clusterSize; i++ )   {
        float err_i = ( ((SSLRobotState)clusterData[i]).velocity - meanVelocity ).lenght2D();
        dataErrors.push_back(err_i);
    }

    for(int i=0; i<3; i++)   {
        vector<float>::iterator max_error_pntr =  max_element(dataErrors.begin(), dataErrors.end());
        if((*max_error_pntr) > 500*pow(2.0, (double)i))   {
            clusterData.erase( (max_error_pntr-dataErrors.begin()) + clusterData.begin() );
            dataErrors.erase( max_error_pntr );
        }
        else {
            break;
        }
    }

    clusterSize = clusterData.size();
    meanVelocity.setZero();
    Vector3D meanPosition;
    for ( int i=0; i<clusterSize; i++ )   {
        meanVelocity += ((SSLRobotState)clusterData[i]).velocity / clusterSize;
        meanPosition += ((SSLRobotState)clusterData[i]).position / clusterSize;
    }
    m_filteredSpeed     = meanVelocity;
    m_filteredPosition  = meanPosition;
    float vision_delay = ParameterManager::getInstance()->get<double>("vision.vision_delay_ms") * 0.001;
    m_filteredPosition += meanVelocity * vision_delay;
    m_filteredPosition.setTeta(getRawData(0).position.Teta());
                //continuousRadian(m_filteredPosition.Teta(), -M_PI));
}

