#ifndef LOOKDIRECTION_H
#define LOOKDIRECTION_H

#include "Point.h"
#include "Direction.h"
#include <math.h>

class LookDirection
{
public:
	LookDirection(Point* from);
	~LookDirection();
	void Init(Point* from);
	float getAzimuth();
	bool isTracking();
	void setTracking(bool tracking);
	void setAzimuth(float azimuth);
	float getElevation();
	void setElevation(float elevation);
	void lookAt(Point* lookFrom,Point* lookAt,bool tracking);
	void lookTo(Direction direction, float magnitude);
	void trackingTick();
	Point* getLookAtPoint();

private:
	void updatePoint();
	void updateAzEl();

private:
	float azimuth;
	float elevation;
	Point* lookAtPoint;
	Point* lookFromPoint;
	bool tracking;
};

#endif

