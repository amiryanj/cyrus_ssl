/*
 * general.h
 *
 *  Created on: Aug 14, 2013
 *      Author: mostafa
 */

#ifndef GENERAL_H_
#define GENERAL_H_

// -------------- G L O B A L   I N C L U D E S ---------
#include <iostream>
#include <math.h>
#include <list>
#include <string>
//#include <vector>
#include "definition/Concepts.h"
#include "tools/vector3d.h"
//using namespace std;
//-------------------------------------------------------

typedef double time_sec;
typedef double time_msec;

typedef double pose_meter;
typedef double pose_mmeter;

typedef Vector3D point3D;

#define SERIAL_PORT "/dev/ttyUSB0"
#define SERIAL_BAUD 115200

#define SSL_VISION_ADDRESS      "224.5.23.2"
#define SSL_VISION_PORT         10002
#define SSL_REFEREE_ADDRESS     "224.5.23.1"
#define SSL_REFEREE_PORT        10003
#define GRSIM_VISION_ADDRESS    "127.0.0.2"
#define GRSIM_VISION_PORT       10002


#define FIELD_WIDTH 4050
#define FIELD_LENGTH  6050
#define FIELD_CENTER_RADIUS 500
#define FIELD_PENALTY_AREA_RADIUS  800
#define FIELD_PENALTY_AREA_WIDTH 350
#define FIELD_GOAL_WIDTH  700
#define FIELD_PENALTY_DISTANCE  750

#define ROBOT_RADIUS 90.0

#define NUM_TEAMS 2
#define MAX_TEAM_PLAYER 6
#define MAX_ID_NUM      12


#endif /* GENERAL_H_ */
