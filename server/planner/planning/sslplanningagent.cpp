#include "sslplanningagent.h"
#include "station.h"

Station &SSLPlanningAgent::step(const Station &st, const Vector3D &global_control, float step_time)
{
    // TODO : consider dynamic constraints of ssl robot
    Station temp_station;
    temp_station.setPosition(st.getPosition() + global_control * step_time);
    return temp_station;
}
