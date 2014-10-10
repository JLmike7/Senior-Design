#include "Position.h"
#include <math.h>

#define RAD2DEG (180.0f/3.14159f)
#define DEG2RAD (3.14159f/180.0f)
#define GRAVITY 9.8


Position::Position()
{
}


Position::~Position()
{
}

void Position::Init(){
	location = new Point(0, 0, 0);
	velocity = new Point(0, 0, 0);
	accel = new Point(0, 0, 0);
}

Point* Position::getLocation(){
	return location;
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
	return velocity;
}

void Position::addVelocity(Point* newSpeed){
	velocity->move(newSpeed);
}

void Position::setVelocity(Point* newSpeed){
	velocity = newSpeed;
}

Point* Position::getAccel(){
	return accel;
}

void Position::setAccel(Point* newAccel){
	accel = newAccel;
}

void Position::addAccel(Point* newAccel){
	accel->move(newAccel);
}

void Position::teleport(Point* coord){
	location = coord;
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
bool Position::isOnGround(){
	//TODO: Make this more intricate to account for other landscapes
	return (location->getX() == 0);
}

void Position::applyTickMovement(){
	//add accel to velocity each tick
	velocity->move(accel);
	//then add velocity to location each tick
	location->move(velocity);
}