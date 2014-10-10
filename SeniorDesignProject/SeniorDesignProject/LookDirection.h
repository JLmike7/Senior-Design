#pragma once
#include "Direction.h"
#include "Point.h"
class LookDirection
{
public:
	LookDirection();
	~LookDirection();
	float getAzimuth();
	void setAzimuth(float azimuth);
	float getElevation();
	void setElevation(float elevation);
	void lookTo(Direction direction,float magnitude);
	void lookAt(Point *point);
	Point* getLookPoint();
private:
	void updatePoint();
	void updateAzEl();

protected:
	float azimuth;
	float elevation;
	Point* point;
};

