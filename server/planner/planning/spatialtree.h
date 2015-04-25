#ifndef _SPATIALTREE_H
#define _SPATIALTREE_H

#include <vector>
#include <assert.h>
#include "spatialvertex.h"

using namespace std;
#define MAX_TREE_CAP  1000

class SpatialTree
{
public:
    SpatialTree() {
        // reserve the array to increase performance
        mVertices.reserve(MAX_TREE_CAP);
    }

    void clear() {
        mVertices.clear();
    }

    int count() const {
        return mVertices.size();
    }

    void setRoot(SpatialVertex* root_) {
        mRoot = root_;
    }

    SpatialVertex* getRoot() const {
        return mRoot;
    }

    SpatialVertex* getVertex(int i) const {
        assert( i >= 0  &&  i < mVertices.size() );
        return mVertices[i];
    }

    SpatialVertex* appendNewStation(SpatialVertex* parent, const Station &st);

    SpatialVertex* getNearestVertex(const Station& st);
    SpatialVertex* lastAddedVertex();

    vector<Station> getStations() const;
protected:
    vector<SpatialVertex*> mVertices;
    SpatialVertex* mRoot;

};

#endif // _SPATIALTREE_H
