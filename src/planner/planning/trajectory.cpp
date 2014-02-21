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

