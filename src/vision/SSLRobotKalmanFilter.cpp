#include "SSLRobotKalmanFilter.h"
#include "definition/sslmath.h"

using namespace std;

SSLRobotKalmanFilter::SSLRobotKalmanFilter()
{    
    Vector3D p_;
    filteredPosition = p_;
    filteredSpeed = p_;

    setDim(6, 0, 3, 3, 3);
    _last_update_time = 0;

    rawPositionList.reserve(MAX_RAW_DATA_MEMORY + 1);


//    runFilter();

}

void SSLRobotKalmanFilter::setNewFrame(const frame &fr)
{
    while(!rawPositionList.empty())
    {
        frame listed_fr = rawPositionList.back();
        if((fr.timeStampMilliSec - listed_fr.timeStampMilliSec) > ((3.0*MAX_RAW_DATA_MEMORY)/(CAMERA_FPS/1000.0)))
            rawPositionList.pop_back();
        else
            break;
    }
    std::vector<frame>::iterator it;
    it = rawPositionList.begin();
    rawPositionList.insert(it, fr);
//    std::cout << "Robot Confidence = " <<fr.confidence << std::endl;
    if(rawPositionList.size() > MAX_RAW_DATA_MEMORY)
        rawPositionList.pop_back();
    _last_interval_time = fr.timeStampMilliSec - _last_update_time;
    _last_update_time = fr.timeStampMilliSec;

}

bool SSLRobotKalmanFilter::isEmpty()
{
    return rawPositionList.empty();
}

bool SSLRobotKalmanFilter::isOnField()
{
    return (rawPositionList.size() >= 4);
}

void SSLRobotKalmanFilter::runFilter()
{
    if( rawPositionList.size() == 0 )
        return;

    frame last_frame = rawPositionList.front();
    Vector3D lastPosition = last_frame.position; // point3D

    if( rawPositionList.size() == 1 )
    {
        Vector init_state(6);
        init_state(1) = lastPosition.X();
        init_state(2) = lastPosition.Y();
        init_state(3) = lastPosition.Teta();

        Matrix init_cov(6, 6);
        for(int i=1; i <= 6; i++)
        {
            // ******************************************
            init_cov(i, i) = 0.0001;
            // ******************************************
        }

        this->init(init_state, init_cov);
        return;
    }

    if( rawPositionList.size() >= 2 )
    {
        Vector obs_pose(3);
        obs_pose(1) = lastPosition.X();
        obs_pose(2) = lastPosition.Y();
        double old_teta = x(3);
        double new_teta = lastPosition.Teta();
        if(old_teta < 0) // && old_teta > -M_PI
             new_teta = continuousRadian(new_teta, -3*M_PI_2);
        else
            new_teta = continuousRadian(new_teta, -M_PI_2);

        obs_pose(3) = new_teta;
        Vector u_(0);
        this->step(u_, obs_pose);

        x(3) = continuousRadian(x(3), -M_PI);

        filteredPosition.setX(x(1));
        filteredPosition.setY(x(2));
        filteredPosition.setTeta(x(3));

        filteredSpeed.setX(x(4));
        filteredSpeed.setY(x(5));
        filteredSpeed.setTeta(x(6));

    }
}

Vector3D SSLRobotKalmanFilter::getFilteredPosition() const
{
    return this->filteredPosition;
}

Vector3D SSLRobotKalmanFilter::getFilteredSpeed() const
{
    return this->filteredSpeed;
}

void SSLRobotKalmanFilter::makeProcess()
{
    Vector temp_x(x.size());
    temp_x(1) = x(1) + _last_interval_time * x(4);
    temp_x(2) = x(2) + _last_interval_time * x(5);
    temp_x(3) = x(3) + _last_interval_time * x(6);

    temp_x(4) = x(4);
    temp_x(5) = x(5);
    temp_x(6) = x(6);

    x.swap(temp_x);
}

void SSLRobotKalmanFilter::makeMeasure()
{
    z(1) = x(1);
    z(2) = x(2);
    z(3) = x(3);
}

void SSLRobotKalmanFilter::makeA()
{
    for(unsigned int i=1; i <= A.nrow(); i++)
        for (unsigned int j=1; j<= A.ncol(); j++)
        {
            if(i != j)
                A(i, j) = 0.0;
            else
                A(i, j) = 1.0;
        }
    A(1, 4) = _last_interval_time;
    A(2, 5) = _last_interval_time;
    A(3, 6) = _last_interval_time;

}

void SSLRobotKalmanFilter::makeW()
{
    for(unsigned int i=1; i <= W.nrow(); i++)
        for (unsigned int j=1; j<= W.ncol(); j++)
            W(i, j) = 0.0;

    W(4, 1) = 5.0;
    W(5, 2) = 5.0;
    W(6, 3) = 5.0;

}

void SSLRobotKalmanFilter::makeH()
{
    for(unsigned int i=1; i <= H.nrow(); i++)
        for (unsigned int j=1; j<= H.ncol(); j++)
        {
            if( i == j)
                H(i, j) = 1.0;
            else
                H(i, j) = 0.0;
        }
}

void SSLRobotKalmanFilter::makeV()
{
    for(unsigned int i=1; i <= V.nrow(); i++)
        for (unsigned int j=1; j<= V.ncol(); j++)
        {
            if( i == j)
                V(i, j) = 1.0;
            else
                V(i, j) = 0.0;
        }
}

void SSLRobotKalmanFilter::makeQ()
{
    // *************************************************
    double q[3] = {1.0, 1.0, 1.0};
    for(unsigned int i=1; i <= Q.nrow(); i++)
        for (unsigned int j=1; j<= Q.ncol(); j++)
        {
            if( i == j)
                Q(i, j) = q[i-1];
            else
                Q(i, j) = 0.0;
        }
}

void SSLRobotKalmanFilter::makeR()
{
    // **************************************************
    cout << "R (Measure noise cov matrix) =  " << endl;
    double r[3] = {10.0, 10.0, 10.0};
    for(unsigned int i=1; i <= R.nrow(); i++) {
        for (unsigned int j=1; j<= R.ncol(); j++)
        {
            if( i == j)
                R(i, j) = r[i-1];
            else
                R(i, j) = 0.0;
            cout << R(i,j) << " ";
        }
        cout << endl;
    }
}

