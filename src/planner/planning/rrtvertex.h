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
    unsigned depth;
    double cost;

    bool hasParent() {
        return (this->parent == NULL);
    }

};

#endif // RRTVERTEX_H
