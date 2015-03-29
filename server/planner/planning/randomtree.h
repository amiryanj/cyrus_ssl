#ifndef RANDOMTREE_H
#define RANDOMTREE_H

#include <stdlib.h>
#include <vector>
#include "station.h"
#include "rrtvertex.h"

using namespace std;
#define MAX_TREE_CAP  10

class RandomTree
{
public:
    RandomTree();
    void clear();
    int count() const;

    void setRoot(RRTVertex* root);
    RRTVertex* getRoot() const;
    RRTVertex* addNewVertex(RRTVertex* parent, Station &st);

    RRTVertex* nearest(const Station& st);
    RRTVertex* lastAddedVertex();

    RRTVertex* getVertex(int i) const;

    vector<Station> getStations() const;
protected:
    vector<RRTVertex*> vertices;
    RRTVertex* root;

};

#endif // RANDOMTREE_H
