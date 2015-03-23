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

    struct PlanCost {
        float length;
        float safety;
        float smoothness;
        void setZero() {
            length = 0;
            safety = 0;
            smoothness = 0;
        }
        PlanCost& operator =(const PlanCost &other) {
            this->length = other.length;
            this->safety = other.safety;
            this->smoothness = other.smoothness;
            return *this;
        }
    } cost;

    static PlanCost cost_weights;


    void computeCost();
    double getCost(float length_w = cost_weights.length,
                   float smooth_w = cost_weights.smoothness,
                   float safety_w = cost_weights.safety) const;

    int length() const;
    bool isEmpty() const;

    void prependState(Station st);
    void appendState(Station st);
    Station removeLastState();

    void printToStream(std::ostream& stream);

//    void setRoot(RRTVertex* m_root);
//    RRTVertex* getRoot() const;

    Station& getStation(uint index);
    void EditStation(uint index, Station &new_st);
    Station getFirstStation();
    Station getLastStation();    
    vector<Station> getAllStations();

    void clear();
    void copyFrom(Trajectory &other);

private:
    Station dummy_station;
    vector<Station> m_states_vec;
};

#endif // TRAJECTORY_H
