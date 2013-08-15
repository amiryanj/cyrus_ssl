/*
 * WorldModel.h
 *
 *  Created on: Aug 14, 2013
 *      Author: mostafa
 */

#ifndef WORLDMODEL_H_
#define WORLDMODEL_H_

#include "../general.h"

class WorldModel {
public:
	WorldModel();
	void updateRobotPosition(int ID, Color color,Position pos);
	virtual ~WorldModel();
};

#endif /* WORLDMODEL_H_ */
