#ifndef RANDOMTREE_H
#define RANDOMTREE_H

#include <stdlib.h>
#include <vector>
#include "station.h"
#include "rrtvertex.h"

using namespace std;
#define MAX_TREE_CAP  500

class RandomTree
{
public:
    RandomTree();
    ~RandomTree();
    void clear();
    int count() const;

    RRTVertex *addNewVertex(RRTVertex* parent, Station &st);

    RRTVertex* nearest(const Station& st);
    RRTVertex* lastAddedVertex();

private:
    RRTVertex* m_vertices[MAX_TREE_CAP];

protected:
    RRTVertex* m_root;
    int m_vertices_count; // 0 -> MAX_TREE_CAP

};

#endif // RANDOMTREE_H
