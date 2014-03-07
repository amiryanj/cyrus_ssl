#include "trajectory.h"

Trajectory::Trajectory()
{
}

Station Trajectory::getStation(int index)
{
    if(index < vertices.size())
        return ((RRTVertex*)(vertices.at(index)))->state;
    return Station();
}

int Trajectory::lenght() const
{
    return this->count();
}

void Trajectory::prependVertex(RRTVertex *ver)
{
    this->vertices.insert(vertices.begin(), 1, ver);
}

void Trajectory::printToStream(ostream &stream)
{
    stream << "*****************************" << endl;
    stream << "Printing   \"T r a j e c t r y\"   Nodes" << endl;
    stream << "*****************************" << endl;
    if(vertices.empty())  {
        stream << "Sorry!!! There is no node in the trajectory created" << endl;
        return;
    }
    std::vector<RRTVertex*>::iterator it;
    int counter = 0;
    for(it = vertices.begin(); it!= vertices.end(); ++it)
    {
        RRTVertex* node = (RRTVertex*)*it;
        stream << "["  << counter++ << "]: X= " << node->state.position.X() << " , Y= " << node->state.position.Y() << endl;
    }
}

