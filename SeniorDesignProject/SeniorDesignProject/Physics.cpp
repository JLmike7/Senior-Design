#include "Physics.h"


Physics::Physics()
{
	gravity = 9.81; //It's like earth, but better
	wind = 3.14;
	groundHeight = 0;
	waterChoppiness = 1;
}


Physics::~Physics()
{
}

void Physics::Init()
{
	
}


double Physics::getGravity(){
	return gravity;
}
void Physics::setGravity(double newGravity){
	gravity = newGravity;
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
float Physics::getWaterChoppiness(){
	return waterChoppiness;
}
void Physics::setWaterChoppiness(float newChoppiness){
	waterChoppiness = newChoppiness;
}
void Physics::enableGravity(Position* pos){
	pos->addAccel(new Point(0, -gravity, 0));
}
void Physics::applyGroundPushback(Position* pos){
	//If on the ground, force Y velocity to zero
	if (!(pos->isOnGround())){
		pos->getVelocity()->setY(0);
	}
}