#ifndef _SPATIAL_VERTEX_H
#define _SPATIAL_VERTEX_H

#include "station.h"

class SpatialVertex
{
public:
    SpatialVertex() { depth = 0; }
    ~SpatialVertex();

    Station state;
    SpatialVertex* parent;
    unsigned depth;
    double cost;

    bool hasParent() {
        return (!this->parent == 0);
    }
};

#endif // _SPATIAL_VERTEX_H
