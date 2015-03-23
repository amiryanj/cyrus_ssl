#include "randomtree.h"
#include <cmath>
#include <iostream>
#include <typeinfo>

using namespace std;

RandomTree::RandomTree()
{
    this->vertices.reserve(MAX_TREE_CAP);
}

void RandomTree::clear()
{
//    for(int i= vertices.size()-1; i>=0; i--)
//        if(vertices.at(i) != NULL)
//            delete vertices.at(i);
    vertices.clear();
}

int RandomTree::count() const
{
    return vertices.size();
}

void RandomTree::setRoot(RRTVertex *root)
{
    this->root = root;
}

RRTVertex *RandomTree::getRoot() const
{
    return this->root;
}

RRTVertex* RandomTree::addNewVertex(RRTVertex *parent, Station &st)
{
    try {
        RRTVertex *new_ver = new RRTVertex();
        new_ver->state = st;
        if(parent == NULL)
            new_ver->depth = 0;
        else
            new_ver->depth = parent->depth + 1;
        new_ver->parent = parent;
        this->vertices.push_back(new_ver);
        return new_ver;
    }
    catch (const char* msg)
    {
        cerr << "Exception " << typeid (*this).name() << " " << msg << endl;
        return NULL;
    }
}

RRTVertex *RandomTree::nearest(const Station &st)
{
    double min_dist = INFINITY;
    RRTVertex* nearest = NULL;
    for(uint i = 0; i<vertices.size(); i++)
    {
        RRTVertex* temp_ver = (RRTVertex*)(vertices[i]);
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

RRTVertex *RandomTree::lastAddedVertex()
{
    try {
    if(vertices.empty())
        throw "there is no vertex in this tree ";
    return this->vertices.back();
    }
    catch (const char* msg) {
        cerr << "Exeption in Random Tree: "  << msg << endl;
        return NULL;
    }
}

RRTVertex *RandomTree::getVertex(int i) const
{
    if(i<0 || i>= vertices.size())
        return NULL;
    return vertices[i];
}

vector<Station> RandomTree::getStations() const
{
    vector<Station> tempVec;
    for(uint i = 0; i<vertices.size(); i++)
        tempVec.push_back(((RRTVertex*)(vertices[i]))->state);
    return tempVec;
}



