#ifndef LOOKDIRECTION_H
#define LOOKDIRECTION_H

#include "Point.h"
#include "Direction.h"
#include <math.h>

class LookDirection{
public:
	LookDirection(float x, float y, float z, Point* _lookat, float _azimuth, float _elevation);
	~LookDirection();

	//void Init(float x, float y, float z, float x1, float y1, float z1);
	float getAzimuth();
	//bool isTracking();
	//void setTracking(bool tracking);
	Point* getlookat();
	void setlookat(Point* _lookat);
	void setAzimuth(float azimuth);
	float getElevation();
	void setElevation(float elevation);
	void lookTo(Direction direction, float magnitude);
	//void lookAt(Point* lookFrom,Point* lookAt,bool tracking);
	//void trackingTick();
	
	//Point* getLookAtPoint();

private:
	void updatePoint();
	//void updateAzEl();

protected:
	Point* lookat;
	float azimuth;
	float elevation;
	//Point* lookAtPoint;
	//Point* lookFromPoint;
	//bool tracking;
};

#endif
