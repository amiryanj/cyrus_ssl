/*
 * general.h
 *
 *  Created on: Aug 14, 2013
 *      Author: mostafa
 */

#ifndef GENERAL_H_
#define GENERAL_H_

#include <iostream>
using namespace std;
#include <math.h>
#include "definition/RobotCommandPacket.h"
#include "definition/Concepts.h"
//#include "definition/Position.h"

#define __SERIAL_PORT "/dev/ttyUSB0"
#define __SERIAL_BAUD 115200
#define __SSL_VISION_ADDRESS "224.5.23.2"
#define __SSL_VISION_PORT 10001
#define __SSL_REFEREE_ADDRESS "224.5.23.1"
#define __SSL_REFEREE_PORT 10003


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
