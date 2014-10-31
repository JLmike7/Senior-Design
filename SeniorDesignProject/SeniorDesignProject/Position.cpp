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

bool Position::isOnGround(){
	//TODO: Make this more intricate to account for other landscapes
	return (location->getX() == 0);
}

void Position::applyTickMovement(){
	//Note:  Flipping the order of these may break ground pushback.
	//apply current velocity to the position
	location->move(velocity);
	//Add acceleration to velocity to set up for next tick.
	velocity->move(accel);
	//Tick the look tracking
	look->trackingTick();
}