#ifndef MOTIONPLANNER_H
#define MOTIONPLANNER_H

#include <ompl/base/Planner.h>
#include <ompl/geometric/PathGeometric.h>
#include <ompl/base/SpaceInformation.h>
#include <ompl/base/spaces/SE2StateSpace.h>
#include <ompl/geometric/planners/rrt/RRTConnect.h>
#include <ompl/geometric/SimpleSetup.h>

#include <ompl/config.h>

#include <boost/units/unit.hpp>
#include <boost/units/dimension.hpp>
#include <boost/units/systems/si/length.hpp>
#include <ompl/base/spaces/RealVectorBounds.h>

using namespace boost::units;
using namespace si;

namespace ob = ompl::base;
namespace og = ompl::geometric;

using namespace ob;

class MotionPlanner
{
public:
    MotionPlanner();

//    const length a_len;

    void initialize(si::length fieldLength, si::length fieldWidth);

private:
//    RealVectorBounds bounds;


};

#endif // MOTIONPLANNER_H
