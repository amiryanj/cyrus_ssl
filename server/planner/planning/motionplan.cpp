#include "motionplan.h"
#include "cmath"

using namespace DMP;

MotionPlan::MotionPlan()
{
    m_station_list.reserve(200);
}

MotionPlan::~MotionPlan()
{
    this->clear();
}

double MotionPlan::cost()
{
    double sum_dist = 0;
    if(m_station_list.empty())
        return sum_dist;
    for (int i=1; i< m_station_list.size(); i++) {
        Vector3D distance = m_station_list[i]->getPosition() - m_station_list[i-1]->getPosition();
        sum_dist += distance.lenght2D();

        float delta_teta = fabs(distance.Teta());
        float rotate_penalty = 1.5 * pow(delta_teta/ (M_PI / 8.0), 3);
        sum_dist += rotate_penalty;
    }
    m_temp_cost = sum_dist;
    return sum_dist;
}

void MotionPlan::append(Station& st)
{
    Station* s1 = new Station();
    (*s1) = st;
    m_station_list.push_back(s1);
}

void MotionPlan::clear()
{
    m_station_list.reserve(5);
    while(!m_station_list.empty()) {
        delete m_station_list.back();
        m_station_list.pop_back();
    }

    m_station_list.clear();
}

int MotionPlan::length()
{
    return m_station_list.size();
}

Station *MotionPlan::getStation(int i)
{
    if(i<0 || i>= m_station_list.size())
        return NULL;
    return m_station_list[i];
}

Station *MotionPlan::getLastStation()
{
    if(m_station_list.empty())
        return NULL;
    return m_station_list.back();
}

MotionPlan &MotionPlan::operator =(MotionPlan &other)
{
    this->clear();
    for (int i=0; i<other.m_station_list.size(); i++) {
        this->append(*(other.m_station_list[i]));
    }
}
