#include "vehicleplanningagent.h"
#include "station.h"
#include "utility/generalmath.h"
#include "utility/vector2d.h"

Station &VehiclePlanningAgent::step(const Station &st, const Vector3D &global_control, float step_time)
{
    // TODO : consider dynamic constraints of ssl robot
    Station temp_station;
    float teta_diff = continuousRadian(global_control.to2D().arctan() - st.getPosition().Teta(), -M_PI);
    float softed_diff = atan(teta_diff) * 0.5;
    Vector2D new_pos = st.getPosition().to2D() + Vector2D::unitVector(st.getPosition().Teta()) * step_time * 30;

    temp_station.setPosition(Vector3D(new_pos, continuousRadian(st.getPosition().Teta() + softed_diff, -M_PI)));

    return temp_station;
}
