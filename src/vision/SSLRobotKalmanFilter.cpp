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

//    setDim(6, 0, 3, 6, 3);
    last_update_time_msec = 0;

    rawPositionList.reserve(MAX_RAW_DATA_MEMORY + 1);


//    runFilter();

}
// insert new frame in the list and remove expired frames
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
    KalmanVector last_observe(6, 1);
    last_observe(0) = last_frame.position.X();
    last_observe(1) = last_frame.position.Y();
    last_observe(2) = last_frame.position.Teta();

    if( rawPositionList.size() == 1 )
    {
//        KalmanVector init_state(6);
//        init_state(0) = lastPosition.X();
//        init_state(1) = lastPosition.Y();
//        init_state(2) = lastPosition.Teta();

//        // using naive kalman filter
//        // ***************************
        naiveFilter.x(0) = last_observe(0);
        naiveFilter.x(1) = last_observe(1);
        naiveFilter.x(2) = last_observe(2);

        naiveFilter.x(3) = 0;
        naiveFilter.x(4) = 0;
        naiveFilter.x(5) = 0;

//        Matrix init_cov(6, 6);
//        for(int i=1; i <= 6; i++)
//        {
//            // this coefficients should be tuned
//            // ******************************************
//            init_cov(i, i) = pow(10, 2);
//            // ******************************************
//        }

//        this->init(init_state, init_cov); // for ekalman filter
        return;
    }

    if( rawPositionList.size() >= 2 )
    {
        {
            double old_teta = naiveFilter.x(2, 0);
            double new_teta = last_observe(2, 0);
            if(old_teta < 0) // && old_teta > -M_PI
                 new_teta = continuousRadian(new_teta, -3*M_PI_2);
            else
                 new_teta = continuousRadian(new_teta, -M_PI_2);
            last_observe(2, 0) = new_teta;
            double delta_teta = new_teta - old_teta;
            delta_teta = continuousRadian(delta_teta, -M_PI_2);
            last_observe(5, 0) = delta_teta/last_interval_time_sec;

            cout << "Orien by kalman: " << old_teta << " , observed= " << new_teta << " , delta= " << delta_teta << endl;
        }
        Vector3D observed_vel;

        frame k1 = rawPositionList.at(0);
        frame k2 = rawPositionList.at(1);

        if(rawPositionList.size()<4)
        {
            observed_vel = (k1.position - k2.position)/last_interval_time_sec;
        }

        else { // using five-point stencil method for computing the velocity
            frame k3 = rawPositionList.at(2);
            frame k4 = rawPositionList.at(3);
            observed_vel = (-k1.position + k2.position * 8 - k3.position * 8 + k4.position)/(12 * last_interval_time_sec);
        }

        last_observe(3, 0) = observed_vel.X();
        last_observe(4, 0) = observed_vel.Y();

        //  using naive kalman filter
        // ******************************************

        naiveFilter.predict(last_interval_time_sec);
        naiveFilter.update(last_observe);
        // ******************************************

        naiveFilter.x(2, 0) = continuousRadian(naiveFilter.x(2), -M_PI);

//        using extended kalman filter
//        Vector u_(0);
//        this->step(u_, las_observe);


        // revision of teta which may be fallen in another range
        filteredPosition.setX(naiveFilter.x(0, 0));
        filteredPosition.setY(naiveFilter.x(1, 0));
        filteredPosition.setTeta(naiveFilter.x(2, 0));

        filteredSpeed.setX(naiveFilter.x(3, 0));
        filteredSpeed.setY(naiveFilter.x(4, 0));
        filteredSpeed.setTeta(naiveFilter.x(5, 0));
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
//void SSLRobotKalmanFilter::makeProcess()
//{
//    Vector temp_x(x.size());
//    temp_x(1) = x(1) + last_interval_time_sec * x(4);
//    temp_x(2) = x(2) + last_interval_time_sec * x(5);
//    temp_x(3) = x(3) + last_interval_time_sec * x(6);

//    temp_x(4) = x(4);
//    temp_x(5) = x(5);
//    temp_x(6) = x(6);

//    x.swap(temp_x);
//}

//// This function works true and needs no more attention: Javad
//// z varible just keeps predicted measures
//void SSLRobotKalmanFilter::makeMeasure()
//{
//    for(unsigned int i=1; i <= getSizeZ(); i++)
//        z(i) = x(i);
//}
//// this function doesn't have any parameter to be tuned !!!
//void SSLRobotKalmanFilter::makeA()
//{
//    // dependence of position on velocity
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
//    for(unsigned int i=1; i<A.nrow()/2; i++) {
//        int j = i+A.nrow()/2;
//        A(i, j) = last_interval_time_sec;
//    }

//}
//// this function doesn't have any parameter to be tuned !!!
////void SSLRobotKalmanFilter::makeBaseA()
////{
////    cout << "A (Jacobian of State matrix) =  " << endl;
////    for(unsigned int i=1; i <= A.nrow(); i++)
////    {
////        for (unsigned int j=1; j<= A.ncol(); j++)
////        {
////            if(i != j)
////                A(i, j) = 0.0;
////            else
////                A(i, j) = 1.0;
////            cout << A(i, j) << "  ";
////        }
////        cout << endl;
////    }
////}

//// process noise
//// only velocity parts of state vector have process noise
//// this function doesn't have any parameter to be tuned !!!
//void SSLRobotKalmanFilter::makeBaseW()
//{
//    cout << "W (Jacobian of Process Noise) =  " << endl;
//    for(unsigned int i=1; i <= W.nrow(); i++)
//    {
//        for (unsigned int j=1; j<= W.ncol(); j++)  {

//            if(i== (j + W.nrow()/2))
//                W(i, j) = 1.0;
//            else
//                W(i, j) = 0.0;
//            cout << W(i, j) << "  ";
//        }
//        cout << endl;
//    }
//}

//// H holds transform from state vector to observation vector
//// this function doesn't have any parameter to be tuned !!!
//void SSLRobotKalmanFilter::makeH()
//{
//    // Identity Matrix
//    cout << "H (Jacobian of Measure Matrix) =  " << endl;
//    for(unsigned int i=1; i <= H.nrow(); i++)
//    {
//        for (unsigned int j=1; j<= H.ncol(); j++)
//        {
//            if( i == j)
//                H(i, j) = 1.0;
//            else
//                H(i, j) = 0.0;
//            cout << H(i,j) << "  ";
//        }
//        cout << endl;
//    }

//}

//// measurement noise
//// noise is present in position values
//// this function doesn't have any parameter to be tuned !!!
//void SSLRobotKalmanFilter::makeBaseV()
//{
//    cout << "V (Jacobian of Measure Noise) =  " << endl;
//    for(unsigned int i=1; i <= V.nrow(); i++)
//    {
//        for (unsigned int j=1; j<= V.ncol(); j++)
//        {
//            if( i == j || i== (j+V.nrow()/2))
//                V(i, j) = 1.0;
//            else
//                V(i, j) = 0.0;
//            cout << V(i,j) << "  ";
//        }
//        cout << endl;
//    }
//}


//// this parameters must be tuned
//void SSLRobotKalmanFilter::makeBaseQ()
//{
//    // *************************************************
//    cout << "Q (Process noise covariance matrix) =  " << endl;
//    // diagonal matrix
//    double q[3] = {100.0, 100.0, 100.0};
//    for(unsigned int i=1; i <= Q.nrow(); i++) {
//        for (unsigned int j=1; j<= Q.ncol(); j++)
//        {
//            if( i == j)
//                Q(i, j) = q[i-1];
//            else
//                Q(i, j) = 0.0;
//            cout << Q(i,j) << "  ";
//        }
//        cout << endl;
//    }
//}

//// this parameters must be tuned
//void SSLRobotKalmanFilter::makeBaseR()
//{
//    // **************************************************
//    cout << "R (Measure noise covariance matrix) =  " << endl;
//    // diagonal matrix
//    double r[3] = {10.0, 10.0, 10.0};
//    for(unsigned int i=1; i <= R.nrow(); i++) {
//        for (unsigned int j=1; j<= R.ncol(); j++)
//        {
//            if( i == j )
//                R(i, j) = r[i-1];
//            else
//                R(i, j) = 0.0;
//            cout << R(i,j) << "  ";
//        }
//        cout << endl;
//    }
//}

