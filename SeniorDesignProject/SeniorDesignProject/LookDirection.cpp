#include "LookDirection.h"

#define RAD2DEG (180.0f/3.14159f)
#define DEG2RAD (3.14159f/180.0f)

LookDirection::LookDirection(float _x, float _y, float _z, Point* _lookat, float _azimuth, float _elevation){
	lookat = _lookat;
	azimuth = _azimuth;
	elevation = _elevation;
}

LookDirection::~LookDirection(){
}

float LookDirection::getAzimuth(){
	return azimuth;
}

void LookDirection::setAzimuth(float _azimuth){
	azimuth = _azimuth;
	updatePoint();
}

Point* LookDirection::getlookat(){
	return lookat;
}

void LookDirection::setlookat(Point* _lookat){
	lookat = _lookat;
}

float LookDirection::getElevation(){
	return elevation;
}

void LookDirection::setElevation(float _elevation){
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
	//Makes up a point exactly 1 unit away from the camera based on the azimuth/elevation.
	lookat->setX(lookat->getX() + (sin(azimuth*DEG2RAD)*sin(elevation*DEG2RAD)));
	lookat->setY(lookat->getY() + (-cos(elevation*DEG2RAD)));
	lookat->setZ(lookat->getZ() + (cos(azimuth*DEG2RAD)*sin(elevation*DEG2RAD)));
}


/*void LookDirection::Init(Point* from){
	azimuth = 0.0f;
	elevation = 90.0f;
	//lookAtPoint = new Point();
	lookFromPoint = from;
	updatePoint();
	tracking = false;
}*/
//TODO: unit tests very much needed
/*void LookDirection::updateAzEl(){
	//Calculates the azimuth and elevation based on where the lookFrom and lookAt points are.
	Point* diffPoint = lookFromPoint->diff(lookAtPoint);
	azimuth = tan(diffPoint->getX() / diffPoint->getZ());
	elevation = -acos(diffPoint->getY());
}

void LookDirection::lookAt(Point* _lookFrom,Point* _lookAt,bool _tracking){
	lookFromPoint = _lookFrom;
	lookAtPoint = _lookAt;
	updateAzEl();
	setTracking(_tracking);
}
Point* LookDirection::getLookAtPoint(){
	return lookAtPoint;
}*/