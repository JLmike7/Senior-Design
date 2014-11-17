#ifndef OBJECTS_H
#define OBJECTS_H

#include "Position.h"
#include "Stats.h"

class Objects {
public:
	Objects(float x, float y, float z, Point lookat, float azimuth, float elevation, Point velocity, int health, int lives);
	~Objects();
	
	//Position* getPosition();
	//void  setPosition(Position *position);

private:
	//Position*	position;
};

#endif

