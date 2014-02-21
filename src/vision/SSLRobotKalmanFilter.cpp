#include "SSLRobotKalmanFilter.h"
#include "definition/sslmath.h"

using namespace std;

int SSLRobotKalmanFilter::state_size = 6;
int SSLRobotKalmanFilter::observe_size = 6;
int SSLRobotKalmanFilter::process_noise_size = 3;
int SSLRobotKalmanFilter::measure_noise_size = 3;

SSLRobotKalmanFilter::SSLRobotKalmanFilter()
{    
    Vector3D p_;
    filteredPosition = p_;
    filteredSpeed = p_;

    setDim(6, 0, 3, 6, 3);
    last_update_time_msec = 0;

    rawPositionList.reserve(MAX_RAW_DATA_MEMORY + 1);


//    runFilter();

}
// insert new frame in thq list and remove expired frames
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
    last_interval_time_sec = (fr.timeStampMilliSec - last_update_time_msec)/ 1000.0;
    last_update_time_msec = fr.timeStampMilliSec;

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

        // using naive kalman filter
        // ***************************
        naiveFilter.x(0, 0) = init_state(1);
        naiveFilter.x(1, 0) = init_state(2);
        naiveFilter.x(2, 0) = init_state(3);

        Matrix init_cov(6, 6);
        for(int i=1; i <= 6; i++)
        {
            // this coefficients should be tuned
            // ******************************************
            init_cov(i, i) = pow(10, 2);
            // ******************************************
        }

        this->init(init_state, init_cov);
        return;
    }

    if( rawPositionList.size() >= 2 )
    {
        Vector last_observe(6);
        last_observe(1) = lastPosition.X();
        last_observe(2) = lastPosition.Y();
        double old_teta = x(3);
        double new_teta = lastPosition.Teta();
        if(old_teta < 0) // && old_teta > -M_PI
             new_teta = continuousRadian(new_teta, -3*M_PI_2);
        else
            new_teta = continuousRadian(new_teta, -M_PI_2);
        last_observe(3) = new_teta;

        frame b = rawPositionList.at(rawPositionList.size()-1);
        frame a = rawPositionList.at(rawPositionList.size()-2);
        Vector3D estimated_vel = (b.position - a.position)/last_interval_time_sec;
        last_observe(4) = estimated_vel.X();
        last_observe(5) = estimated_vel.Y();
        last_observe(6) = (b.position.Teta() - a.position.Teta())/last_interval_time_sec;

        //  using naive kalman filter
        // ******************************************

        naiveFilter.delta_t_sec = last_interval_time_sec;
        naiveFilter.predict();
        NaiveKalmanFilter::KalmanVector observation_;
        observation_(0,0) = last_observe(1);
        observation_(1,0) = last_observe(2);
        observation_(2,0) = last_observe(3);
        observation_(3,0) = last_observe(4);
        observation_(4,0) = last_observe(5);
        observation_(5,0) = last_observe(6);
        naiveFilter.update(observation_);
        x(1) = naiveFilter.x(0,0);
        x(2) = naiveFilter.x(1,0);
        x(3) = naiveFilter.x(2,0);
        x(4) = naiveFilter.x(3,0);
        x(5) = naiveFilter.x(4,0);
        x(6) = naiveFilter.x(5,0);

        // ******************************************


//        Vector u_(0);
//        this->step(u_, las_observe);

        // revision of teta which may fall in another range
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

// new x would possess new predicted state
void SSLRobotKalmanFilter::makeProcess()
{
    Vector temp_x(x.size());
    temp_x(1) = x(1) + last_interval_time_sec * x(4);
    temp_x(2) = x(2) + last_interval_time_sec * x(5);
    temp_x(3) = x(3) + last_interval_time_sec * x(6);

    temp_x(4) = x(4);
    temp_x(5) = x(5);
    temp_x(6) = x(6);

    x.swap(temp_x);
}

// This function works true and needs no more attention: Javad
// z varible just keeps predicted measures
void SSLRobotKalmanFilter::makeMeasure()
{
    for(unsigned int i=1; i <= getSizeZ(); i++)
        z(i) = x(i);
}
// this function doesn't have any parameter to be tuned !!!
void SSLRobotKalmanFilter::makeA()
{
    // dependence of position on velocity
    for(unsigned int i=1; i <= A.nrow(); i++)
    {
        for (unsigned int j=1; j<= A.ncol(); j++)
        {
            if(i != j)
                A(i, j) = 0.0;
            else
                A(i, j) = 1.0;
            cout << A(i, j) << "  ";
        }
        cout << endl;
    }
    for(unsigned int i=1; i<A.nrow()/2; i++) {
        int j = i+A.nrow()/2;
        A(i, j) = last_interval_time_sec;
    }
//    A(1, 4) = _last_interval_time;
//    A(2, 5) = _last_interval_time;
//    A(3, 6) = _last_interval_time;

}
// this function doesn't have any parameter to be tuned !!!
//void SSLRobotKalmanFilter::makeBaseA()
//{
//    cout << "A (Jacobian of State matrix) =  " << endl;
//    for(unsigned int i=1; i <= A.nrow(); i++)
//    {
//        for (unsigned int j=1; j<= A.ncol(); j++)
//        {
//            if(i != j)
//                A(i, j) = 0.0;
//            else
//                A(i, j) = 1.0;
//            cout << A(i, j) << "  ";
//        }
//        cout << endl;
//    }
//}

// process noise
// only velocity parts of state vector have process noise
// this function doesn't have any parameter to be tuned !!!
void SSLRobotKalmanFilter::makeBaseW()
{
    cout << "W (Jacobian of Process Noise) =  " << endl;
    for(unsigned int i=1; i <= W.nrow(); i++)
    {
        for (unsigned int j=1; j<= W.ncol(); j++)  {

            if(i== (j + W.nrow()/2))
                W(i, j) = 1.0;
            else
                W(i, j) = 0.0;
            cout << W(i, j) << "  ";
        }
        cout << endl;
    }

//    W(4, 1) = 1.0;
//    W(5, 2) = 1.0;
//    W(6, 3) = 1.0;
}

// H holds transform from state vector to observation vector
// this function doesn't have any parameter to be tuned !!!
void SSLRobotKalmanFilter::makeH()
{
    // Identity Matrix
    cout << "H (Jacobian of Measure Matrix) =  " << endl;
    for(unsigned int i=1; i <= H.nrow(); i++)
    {
        for (unsigned int j=1; j<= H.ncol(); j++)
        {
            if( i == j)
                H(i, j) = 1.0;
            else
                H(i, j) = 0.0;
            cout << H(i,j) << "  ";
        }
        cout << endl;
    }

}

// measurement noise
// noise is present in position values
// this function doesn't have any parameter to be tuned !!!
void SSLRobotKalmanFilter::makeBaseV()
{
    cout << "V (Jacobian of Measure Noise) =  " << endl;
    for(unsigned int i=1; i <= V.nrow(); i++)
    {
        for (unsigned int j=1; j<= V.ncol(); j++)
        {
            if( i == j || i== (j+V.nrow()/2))
                V(i, j) = 1.0;
            else
                V(i, j) = 0.0;
            cout << V(i,j) << "  ";
        }
        cout << endl;
    }
}


// this parameters must be tuned
void SSLRobotKalmanFilter::makeBaseQ()
{
    // *************************************************
    cout << "Q (Process noise covariance matrix) =  " << endl;
    // diagonal matrix
    double q[3] = {100.0, 100.0, 100.0};
    for(unsigned int i=1; i <= Q.nrow(); i++) {
        for (unsigned int j=1; j<= Q.ncol(); j++)
        {
            if( i == j)
                Q(i, j) = q[i-1];
            else
                Q(i, j) = 0.0;
            cout << Q(i,j) << "  ";
        }
        cout << endl;
    }
}

// this parameters must be tuned
void SSLRobotKalmanFilter::makeBaseR()
{
    // **************************************************
    cout << "R (Measure noise covariance matrix) =  " << endl;
    // diagonal matrix
    double r[3] = {10.0, 10.0, 10.0};
    for(unsigned int i=1; i <= R.nrow(); i++) {
        for (unsigned int j=1; j<= R.ncol(); j++)
        {
            if( i == j )
                R(i, j) = r[i-1];
            else
                R(i, j) = 0.0;
            cout << R(i,j) << "  ";
        }
        cout << endl;
    }
}

