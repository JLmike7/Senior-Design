#include "Position.h"
#include <math.h>

#define RAD2DEG (180.0f/3.14159f)
#define DEG2RAD (3.14159f/180.0f)


Position::Position()
{
}


Position::~Position()
{
}

void Position::Init(){
	location = (0, 0, 0);
	speed = (0, 0, 0);
	accel = (0, 0, 0);
}

//Getters/Settings for Stats.
Point* Position::getLocation(){
	return location;
}

void Position::setLocation(Point* point){
	location = point;
}

LookDirection* Position::getLook(){
	return look;
}

void Position::lookTo(Direction direction,float magnitude){
	look->lookTo(direction,magnitude);
}

void Position::lookAt(Point* point){
	look->lookAt(point);
}

Point* Position::getVelocity(){
	return speed;
}

void Position::setVelocity(Point* newSpeed){
	speed = newSpeed;
}

Point* Position::getAccel(){
	return accel;
}

void Position::setAccel(Point* newAccel){
	accel = newAccel;
}

void Position::teleport(Point* coord){
	setLocation(coord);
}

void Position::move(Direction direction,float magnitude){
	float azimuth = look->getAzimuth();
	if (direction == Direction::FRONT){
		location->moveX(sin(azimuth*DEG2RAD)*magnitude);
		location->moveZ(cos(azimuth*DEG2RAD)*magnitude);
	}
	if (direction == Direction::BACK){
		location->moveX(-sin(azimuth*DEG2RAD)*magnitude);
		location->moveZ(-cos(azimuth*DEG2RAD)*magnitude);
	}
	if (direction == Direction::LEFT){
		location->moveX(sin((90 + azimuth)*DEG2RAD)*magnitude);
		location->moveZ(cos((90 + azimuth)*DEG2RAD)*magnitude);
	}
	if (direction == Direction::RIGHT){
		location->moveX(-sin((90 + azimuth)*DEG2RAD)*magnitude);
		location->moveZ(-cos((90 + azimuth)*DEG2RAD)*magnitude);
	}
	if (direction == Direction::UP){
		//Camera shouldn't matter what direction is up/down
		location->moveY(magnitude);
	}
	if (direction == Direction::DOWN){
		//Camera shouldn't matter what direction is up/down
		location->moveY(magnitude);
	}

}