#ifndef _ROBOTCLUSTERFILTER_H
#define _ROBOTCLUSTERFILTER_H

#include <vector>
#include <stdlib.h>
#include "sslframe.h"
#include "alphabetafilter.h"
#include "../../shared/utility/vector3d.h"
#include "../definition/SSLRobot.h"
#include "robotfilter.h"

class RobotClusterFilter : public RobotFilter
{
    friend class VisionFilter;
    friend class MainWindow;
public:
    RobotClusterFilter();
    bool run();
};

#endif // _ROBOTCLUSTERFILTER_H
