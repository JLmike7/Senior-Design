#pragma once
#include "Direction.h"
#include "Point.h"

class LookDirection
{
public:
	LookDirection();
	~LookDirection();
	void Init();
	float getAzimuth();
	bool isTracking();
	void setTracking(bool tracking);
	void setAzimuth(float azimuth);
	float getElevation();
	void setElevation(float elevation);
	void lookTo(Direction direction,float magnitude);
	void lookAt(Point *point,bool tracking);
	void trackingTick();
	Point* getLookPoint();

private:
	void updatePoint();
	void updateAzEl();

protected:
	float azimuth;
	float elevation;
	Point* point;
	bool tracking;
};

