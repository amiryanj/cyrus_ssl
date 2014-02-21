#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <vector>
#include <stdlib.h>
#include "station.h"
#include "randomtree.h"

class Trajectory : public RandomTree
{
public:
    Trajectory();    
    double cost();

    int lenght() const;

    void prependVertex(RRTVertex* ver);

    Station getStation(int index);
};

#endif // TRAJECTORY_H
