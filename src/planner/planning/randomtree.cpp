#include "randomtree.h"
#include <cmath>
#include <iostream>
#include <typeinfo>
#include <assert.h>

using namespace std;

RandomTree::RandomTree()
{
    for(int i=0; i<MAX_TREE_CAP; i++) {
        m_vertices[i] = new RRTVertex();
    }
}

RandomTree::~RandomTree()
{
    for(int i=0; i<MAX_TREE_CAP; i++) {
        delete m_vertices[i];
    }
}

void RandomTree::clear()
{
//    for(int i= m_vertices.size()-1; i>=0; i--)
//        if(m_vertices.at(i) != NULL)
//            delete m_vertices.at(i);
//    m_vertices.clear();
    m_vertices_count = 0;
}

int RandomTree::count() const
{
//    return m_vertices.size();
    return m_vertices_count;
}

RRTVertex* RandomTree::addNewVertex(RRTVertex *parent, Station &st)
{
    try {
//        RRTVertex *new_ver = new RRTVertex();
//        assert(m_vertices_count >= 0);
        RRTVertex* new_ver = m_vertices[m_vertices_count];
        new_ver->state = st;
        if(parent == NULL)
            new_ver->depth = 0;
        else
            new_ver->depth = parent->depth + 1;
        new_ver->parent = parent;
        m_vertices_count ++;
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
    try {
        double min_dist = INFINITY;
        RRTVertex* nearest = NULL;
        if(m_vertices_count <= 0)
            throw "Tree is empty";
        if(st.position.isInf())
            throw "The State position is placed in infinity...";
        for(int i = 0; i<m_vertices_count; i++)
        {
            RRTVertex* temp_ver = m_vertices[i];
            double temp_dist = (temp_ver->state.getPosition() - st.getPosition()).lenght2D();
            if(temp_dist < min_dist)
            {
                min_dist = temp_dist;
                nearest = temp_ver;
            }
        }
        if(min_dist == INFINITY)
            throw "nearest dist is INFINITY!" ;
        return nearest;
    }
    catch (const char* msg) {
        cerr << "Exception: " << "RandomTree" << msg << endl;
        return NULL;
    }
}

RRTVertex *RandomTree::lastAddedVertex()
{
    try {
        if(m_vertices_count <= 0)
            throw "there is no vertex in this tree ";
        else
            return m_vertices[m_vertices_count-1];
    }
    catch (const char* msg) {
        cerr << "Exeption in Random Tree: "  << msg << endl;
        return NULL;
    }
}





