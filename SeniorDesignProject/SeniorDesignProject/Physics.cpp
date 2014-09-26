#include "Physics.h"


Physics::Physics()
{
}


Physics::~Physics()
{
}

void Physics::Init()
{
	gravity = 9.81; //It's like earth, but better
	wind = 3.14;
	groundHeight = 0;
	waterChoppiness = 1;
}


float Physics::getGravity(){
	return gravity;
}
void Physics::setGravity(float newGravity){
	gravity = newGravity;
}
float Physics::getWind(){
	return wind;
}
void Physics::setWind(float newWind){
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
