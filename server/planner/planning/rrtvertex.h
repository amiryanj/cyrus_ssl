#ifndef RRTVERTEX_H
#define RRTVERTEX_H

#include <stdlib.h>
#include "station.h"

class RRTVertex
{
public:
    RRTVertex();
    ~RRTVertex();

    Station state;
    RRTVertex* parent;
    RRTVertex* child;
    unsigned depth;
    double cost;

    bool hasParent() {
        return (!this->parent == 0);
    }

    bool hasChild() {
        return (!this->child == 0);
    }

};

#endif // RRTVERTEX_H
