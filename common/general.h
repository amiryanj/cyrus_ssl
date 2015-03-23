#ifndef _GENERAL_H_
#define _GENERAL_H_

// -------------- G L O B A L   I N C L U D E S ---------
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "Concepts.h"
#include "math/vector3d.h"
#include "math/vector2d.h"
//using namespace std;
//-------------------------------------------------------


#define SERIAL_PORT "/dev/ttyUSB0"
#define SERIAL_BAUD 115200

#define FIELD_WIDTH                 4050.0
#define FIELD_LENGTH                6050.0
#define FIELD_CENTER_RADIUS         500.0
#define FIELD_PENALTY_AREA_RADIUS   900.0
#define FIELD_PENALTY_AREA_WIDTH    350.0
#define FIELD_GOAL_WIDTH            700.0
#define FIELD_PENALTY_DISTANCE      750.0

#define ROBOT_RADIUS        90.0
#define BALL_RADIUS         21.5

#define NUM_TEAMS           2
#define MAX_TEAM_PLAYER     6
#define MAX_ID_NUM          12


#endif /* _GENERAL_H_ */
