#include "LookDirection.h"
#include <math.h>

#define RAD2DEG (180.0f/3.14159f)
#define DEG2RAD (3.14159f/180.0f)

LookDirection::LookDirection()
{
	azimuth = 0.0;
	elevation = 90.0;
	updatePoint();
}


LookDirection::~LookDirection()
{

}

float LookDirection::getAzimuth(){
	return azimuth;
}

void LookDirection::setAzimuth(float _azimuth){
	azimuth = _azimuth;
	updatePoint();
}

float LookDirection::getElevation(){
	return elevation;
}

void LookDirection::setAzimuth(float _elevation){
	elevation = _elevation;
	updatePoint();
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
//TODO: unit tests very much needed
void LookDirection::updatePoint(){
	point->setX(sin(azimuth*DEG2RAD)*sin(elevation*DEG2RAD));
	point->setY(-cos(elevation*DEG2RAD));
	point->setZ(cos(azimuth*DEG2RAD)*sin(elevation*DEG2RAD));
}
//TODO: unit tests very much needed
void LookDirection::updateAzEl(){
	azimuth=tan(point->getX() / point->getZ());
	elevation = -acos(point->getY());
}

void LookDirection::lookAt(Point* _point){
	point = _point;
	updateAzEl();
}

Point* LookDirection::getLookPoint(){
	return point;
}
