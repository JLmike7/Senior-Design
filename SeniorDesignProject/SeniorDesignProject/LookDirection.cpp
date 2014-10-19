#include "LookDirection.h"
#include <math.h>

#define RAD2DEG (180.0f/3.14159f)
#define DEG2RAD (3.14159f/180.0f)

LookDirection::LookDirection()
{
	Init();
}


LookDirection::~LookDirection()
{

}

void LookDirection::Init(){
	azimuth = 0.0;
	elevation = 90.0;
	updatePoint();
	tracking = false;
}

float LookDirection::getAzimuth(){
	return azimuth;
}

void LookDirection::setAzimuth(float _azimuth){
	azimuth = _azimuth;
	updatePoint();
	tracking = false;
}

float LookDirection::getElevation(){
	return elevation;
}

void LookDirection::setElevation(float _elevation){
	elevation = _elevation;
	updatePoint();
	tracking = false;
}

void LookDirection::lookTo(Direction direction, float magnitude){
	if (direction == Direction::DOWN){
		elevation -= magnitude;
	}
	else if (direction == Direction::UP){
		elevation += magnitude;
	}
	else if (direction == Direction::LEFT){
		azimuth -= magnitude;
	}
	else if (direction == Direction::RIGHT){
		azimuth += magnitude;
	}
	else{
		//TODO: error-invalid direction
	}
	updatePoint();
}

bool LookDirection::isTracking(){
	return tracking;
}
void LookDirection::setTracking(bool _tracking){
	tracking = _tracking;
}

//TODO: unit tests very much needed
void LookDirection::updatePoint(){
	//Makes up a point exactly 1 unit away from the camera based on the azimuth/elevation.
	lookAtPoint->setX( lookFromPoint->getX() + (sin(azimuth*DEG2RAD)*sin(elevation*DEG2RAD)));
	lookAtPoint->setY( lookFromPoint->getY() + (-cos(elevation*DEG2RAD)));
	lookAtPoint->setZ( lookFromPoint->getZ() + (cos(azimuth*DEG2RAD)*sin(elevation*DEG2RAD)));
}
//TODO: unit tests very much needed
void LookDirection::updateAzEl(){
	//Calculates the azimuth and elevation based on where the lookFrom and lookAt points are.
	Point* diffPoint = lookFromPoint->diff(lookAtPoint);
	azimuth = tan(diffPoint->getX() / diffPoint->getZ());
	elevation = -acos(diffPoint->getY());
}

void LookDirection::trackingTick(){
	if (tracking)
		updateAzEl();
}

void LookDirection::lookAt(Point* _lookFrom,Point* _lookAt,bool _tracking){
	lookFromPoint = _lookFrom;
	lookAtPoint = _lookAt;
	updateAzEl();
	setTracking(_tracking);
}
Point* LookDirection::getLookAtPoint(){
	return lookAtPoint;
}