#include "trajectory.h"
#include <math.h>

Trajectory::Trajectory()
{
}

Station Trajectory::getStation(int index)
{
    if(index < m_vertex_vec.size())
        return ((RRTVertex*)(m_vertex_vec.at(index)))->state;
    return Station();
}

vector<Station> Trajectory::getAllStations()
{
    vector<Station> tempVec;
    for(int i = 0; i<m_vertex_vec.size(); i++)
        tempVec.push_back(((RRTVertex*)(m_vertex_vec[i]))->state);
    return tempVec;
}

RRTVertex *Trajectory::getVertex(int i)
{
    if(i >= m_vertex_vec.size())
        return NULL;
    return m_vertex_vec.at(i);
}

void Trajectory::clear()
{
    m_vertex_vec.clear();
}

int Trajectory::lenght() const
{
    return m_vertex_vec.size();
}

void Trajectory::prependVertex(RRTVertex *ver)
{
    this->m_vertex_vec.insert(m_vertex_vec.begin(), ver);
}

void Trajectory::printToStream(ostream &stream)
{
    stream << "*****************************" << endl;
    stream << "Printing   \"T r a j e c t r y\"   Nodes" << endl;
    stream << "*****************************" << endl;
    if(m_vertex_vec.empty())  {
        stream << "Sorry!!! There is no node in the trajectory created" << endl;
        return;
    }
    std::vector<RRTVertex*>::iterator it;
    int counter = 0;
    for(it = m_vertex_vec.begin(); it!= m_vertex_vec.end(); ++it)
    {
        RRTVertex* node = (RRTVertex*)*it;
        stream << "["  << counter++ << "]: {X= " << node->state.position.X()
                                    << " , Y= " << node->state.position.Y()
                                    << " , O= " << node->state.position.Teta() * 180/M_PI << " deg}";
        stream << " {Vx= " << node->state.velo.X()
               << ", Vy= " << node->state.velo.Y()
               << ", Wz= " << node->state.velo.Teta() * 180/M_PI << " deg/s}" << endl;
    }
}

