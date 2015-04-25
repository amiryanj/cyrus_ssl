#ifndef _TRAJECTORY_H
#define _TRAJECTORY_H

#include <vector>
#include <stdlib.h>
#include <ostream>
#include "station.h"
#include "spatialtree.h"
#include "vector2d.h"
#include "vector3d.h"
#include "utility/generalmath.h"

class Trajectory
{
public:
    Trajectory();

    ~Trajectory();
    void clear();

    void copyFrom(Trajectory &other);
//    Trajectory& operator =(Trajectory & other);

    int length() const;
    bool isEmpty() const;

    void prependState(const Station &st);
    void appendState(const Station &st);
    Station removeLastState();


    void EditStation(uint index, const Station &new_st);

    Station& getStation(uint index) const;
    Station getFirstStation() const;
    Station getLastStation() const;
    vector<Station> getAllStations();


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

    void printToStream(std::ostream& stream);
private:
    vector<Station> m_states_vec;
};

#endif // TRAJECTORY_H
