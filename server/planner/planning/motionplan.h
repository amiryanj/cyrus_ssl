#ifndef _PLANNINGPLAN_H
#define _PLANNINGPLAN_H
#include "station.h"
#include <vector>

using namespace std;

namespace DMP {
    class MotionPlan
    {
    public:
        MotionPlan();
        ~MotionPlan();
        double cost();

        void append(Station &st);
        void clear();
        int length();

        bool valid;

        Station* getStation(int i);
        Station* getLastStation();

        vector<Station*> m_station_list;

        MotionPlan& operator =(MotionPlan& other);
    private:
        double m_temp_cost;

    };
}

#endif // _PLANNINGPLAN_H
