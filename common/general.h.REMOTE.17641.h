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

typedef double time_sec;
typedef double time_msec;

typedef double pose_meter;
typedef double pose_mmeter;

typedef Vector3D point3D;

#define SERIAL_PORT "/dev/ttyUSB0"
#define SERIAL_BAUD 115200

#define MY_REFEREE_ADDRESS     "127.0.0.2"
#define MY_REFEREE_PORT         10004

#define SSL_REFEREE_ADDRESS     "224.5.23.1"
#define SSL_REFEREE_PORT        10001

//static const char* SSL_VISION_ADDRESS = "224.5.23.2";
#define SSL_VISION_ADDRESS      "224.5.23.2"
#define SSL_VISION_PORT         10002

#define GRSIM_VISION_ADDRESS    "127.0.0.1"
#define GRSIM_VISION_PORT       10005

#define GRSIM_COMMAND_ADDRESS   "127.0.0.1"
// "192.168.1.105"
#define GRSIM_COMMAND_PORT      20011

#define VISUALIZER_IP           "127.0.0.1"
// "213.233.171.39" //
#define VISUALIZER_PORT         4001


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
