#ifndef STATE_H
#define STATE_H

#include "../tools/vector2d.h"

namespace Planner{
    class State
    {
    public:
        State();
    //    State(State &other);
        State(Vector2D pos, double head, double vel);

        Vector2D position;
        double heading;
        double curvature;
        double velocity;

        bool isNull();

        State operator -(State other);
        State operator +(State other);
        State& operator *=(double mul);
        double distTo(const State &other);
        double distToB(const State &other);
        bool operator==(State other);

        State& operator =(State other);

    };
}

#endif // STATE_H
