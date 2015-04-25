#include "trajectory.h"
#include <math.h>
#include <assert.h>

Trajectory::PlanCost Trajectory::cost_weights;
Trajectory::Trajectory()
{
    m_states_vec.reserve(100);
    cost.length = INFINITY;
    cost.smoothness = INFINITY;
    cost.safety = INFINITY;
}

Trajectory::~Trajectory()
{
    m_states_vec.clear();
}

void Trajectory::computeCost()
{
    if(m_states_vec.empty())
        return;
    this->cost.length = 0;
    this->cost.smoothness = 0;
    this->cost.safety = 0;

    for (uint i=0; i< m_states_vec.size(); i++)  {
        if(i == 0) {
            m_states_vec[i].cost.setZero();
            continue;
        }
        Vector3D dist_i = m_states_vec[i].getPosition() - m_states_vec[i-1].getPosition();
        this->cost.length += dist_i.lenght2D();

        float delta_teta = dist_i.Teta();
        m_states_vec[i].cost.delta_heading = delta_teta;

        this->cost.smoothness += m_states_vec[i].cost.smooth_penalty();
    }

}

void Trajectory::EditStation(uint index, const Station &new_st)
{
    assert(index < m_states_vec.size());
    this->m_states_vec[index] = new_st;
}

Station &Trajectory::getStation(uint index) const
{
    Station st;
    if(index < m_states_vec.size()) {
        st = m_states_vec[index];
        return st;
    }
    assert(0);
}

Station Trajectory::getFirstStation() const
{
    if(this->isEmpty())
        return Station();
    return getStation(0);
}

Station Trajectory::getLastStation() const
{
    if(this->isEmpty())
        return Station();
    return getStation(this->length() - 1);
}

vector<Station> Trajectory::getAllStations()
{
    return m_states_vec;
}

void Trajectory::clear()
{
    m_states_vec.clear();
}

void Trajectory::copyFrom(Trajectory &other)
{
    m_states_vec.clear();
    for(int i=0; i<other.length(); i++) {
        Station st = other.getStation(i);
        this->appendState(st);
    }
    this->cost = other.cost;
}

//Trajectory &Trajectory::operator =(Trajectory &other)
//{
//    this->copyFrom(other);
//}

double Trajectory::getCost(float length_w, float smooth_w, float safety_w) const
{
    return (fabs(cost.length) * length_w + fabs(cost.smoothness) * smooth_w + fabs(cost.safety) * safety_w);
}

int Trajectory::length() const
{
    return m_states_vec.size();
}

bool Trajectory::isEmpty() const
{
    return m_states_vec.empty();
}

void Trajectory::prependState(const Station &st)
{
    this->m_states_vec.insert(m_states_vec.begin(), st);
}

void Trajectory::appendState(const Station &st)
{
    this->m_states_vec.insert(m_states_vec.end(), st);
}

Station Trajectory::removeLastState()
{
    if(m_states_vec.empty())
        return Station();
    Station st = m_states_vec.back();
    m_states_vec.pop_back();
    return st;
}

void Trajectory::printToStream(ostream &stream)
{
    stream << "*****************************" << endl;
    stream << "Printing   \"T r a j e c t r y\"   Nodes" << endl;
    stream << "*****************************" << endl;
    cout << "Total Costs: " << "[Length = " << cost.length
                         << "], [Safety = " << cost.safety
                         << "], [Smoothness = " << cost.smoothness << "]" << endl;
    if(m_states_vec.empty())  {
        stream << "Sorry!!! There is no node in the trajectory created" << endl;
        return;
    }

    for(uint s=0 ; s< m_states_vec.size(); s++)
    {
        std::cout << s;
        m_states_vec[s].printToStream(std::cout);
//        stream << "["  << counter++ << "]: {X= " << m_states_vec[s].getPosition().X()
//                                    << " , Y= " << m_states_vec[s].getPosition().Y()
//                                    << " , O= " << m_states_vec[s].getPosition().Teta() * 180/M_PI << " deg}";
//        stream << " {Vx= " << m_states_vec[s].getVelocity().X()
//               << ", Vy= " << m_states_vec[s].getVelocity().Y()
//               << ", Wz= " << m_states_vec[s].getVelocity().Teta() * 180/M_PI << " deg/s}" << endl;
    }
}

