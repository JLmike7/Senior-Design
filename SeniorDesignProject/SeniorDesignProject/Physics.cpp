#include "Physics.h"

#define GRAVITY 9.81f
#define WATER_CHOPPYNESS 1

Physics::Physics()
{
	wind = 3.14;
	groundHeight = 0;
}


Physics::~Physics()
{
}

void Physics::Init()
{
	
}

double Physics::getWind(){
	return wind;
}
void Physics::setWind(double newWind){
	wind = newWind;
}
float Physics::getGroundHeight(){
	return groundHeight;
}
void Physics::setGroundHeight(float newHeight){
	groundHeight = newHeight;
}
void Physics::enableGravity(Position* pos){
	pos->getAccel()->addY(-GRAVITY);
}
void Physics::applyGroundPushback(Position* pos){
	//If on the ground, take away gravity by undoing the gravity's acceleration for this tick
	if (!(pos->isOnGround())){
		pos->getVelocity()->addY(GRAVITY);
	}
}