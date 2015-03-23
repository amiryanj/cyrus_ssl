#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <vector>
#include <stdlib.h>
#include <ostream>
#include "station.h"
#include "randomtree.h"

class Trajectory
{
public:
    Trajectory();    
    double cost();

    uint lenght() const;

    void prependVertex(RRTVertex* ver);

    void printToStream(std::ostream& stream);

//    void setRoot(RRTVertex* m_root);
//    RRTVertex* getRoot() const;

    Station getStation(uint index);
    vector<Station> getAllStations();
    RRTVertex* getVertex(uint index);

    void clear();

private:
    vector<RRTVertex*> m_vertex_vec;


};

#endif // TRAJECTORY_H
