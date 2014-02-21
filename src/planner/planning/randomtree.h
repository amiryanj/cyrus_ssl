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
    void clear();
    int count() const;

    void setRoot(RRTVertex* root);
    RRTVertex* getRoot() const;
    bool addNewVertex(RRTVertex* parent, Station &st);

    RRTVertex* nearest(const Station& st);
    RRTVertex* lastAddedVertex();

    vector<Station> getStations() const;
protected:
    vector<RRTVertex*> vertices;
    RRTVertex* root;

};

#endif // RANDOMTREE_H
