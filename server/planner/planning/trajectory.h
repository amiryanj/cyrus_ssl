#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <vector>
#include <stdlib.h>
#include "station.h"
#include "randomtree.h"
#include "ostream"

class Trajectory
{
public:
    Trajectory();    
    double cost();

    int lenght() const;

    void prependVertex(RRTVertex* ver);

    void printToStream(std::ostream& stream);

//    void setRoot(RRTVertex* m_root);
//    RRTVertex* getRoot() const;

    Station getStation(int index);
    vector<Station> getAllStations();
    RRTVertex* getVertex(int index);

    void clear();

private:
    vector<RRTVertex*> m_vertex_vec;


};

#endif // TRAJECTORY_H
