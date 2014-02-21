#ifndef RRTVERTEX_H
#define RRTVERTEX_H

#include <stdlib.h>
#include <station.h>

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
        return (!this->parent == NULL);
    }

    bool hasChild() {
        return (!this->child == NULL);
    }

};

#endif // RRTVERTEX_H
