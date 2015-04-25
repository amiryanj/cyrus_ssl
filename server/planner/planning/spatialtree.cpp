#include "spatialtree.h"
#include <cmath>
#include <iostream>
#include <typeinfo>
#include <sys/types.h>

using namespace std;

SpatialVertex* SpatialTree::appendNewStation(SpatialVertex *parent, const Station &st)
{
    try {
        SpatialVertex *new_ver = new SpatialVertex;
        new_ver->state = st;
        if(parent == NULL)
            new_ver->depth = 0;
        else
            new_ver->depth = parent->depth + 1;
        new_ver->parent = parent;
        this->mVertices.push_back(new_ver);
        return new_ver;
    }
    catch (const char* msg)
    {
        cerr << "Exception " << typeid (*this).name() << " " << msg << endl;
        return NULL;
    }
}

SpatialVertex *SpatialTree::getNearestVertex(const Station &st)
{
    // TODO : use KD-tree structure to apeed up this process
    double min_dist = INFINITY;
    SpatialVertex* nearest = NULL;
    for(uint i = 0; i<mVertices.size(); i++)
    {
        SpatialVertex* temp_ver = mVertices[i];
//        double temp_dist = Station::euclideanDistance(temp_ver->state, st); // temporal
        double temp_dist = Station::dubinDistance(temp_ver->state, st);
        if(temp_dist <= min_dist)
        {
            min_dist = temp_dist;
            nearest = temp_ver;
        }
    }
    return nearest;
}

SpatialVertex *SpatialTree::lastAddedVertex()
{
    try {
    if(mVertices.empty())
        throw "there is no vertex in this tree ";
    return this->mVertices.back();
    }
    catch (const char* msg) {
        cerr << "Exeption in Random Tree: "  << msg << endl;
        return NULL;
    }
}

vector<Station> SpatialTree::getStations() const
{
    vector<Station> tempVec;
    for(uint i = 0; i<mVertices.size(); i++)
        tempVec.push_back(((SpatialVertex*)(mVertices[i]))->state);
    return tempVec;
}



