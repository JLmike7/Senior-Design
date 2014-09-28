#include "Person.h"


Person::Person()
{

}


Person::~Person()
{
}

void Person::Init()
{
	//stance = Stance->STANDBY;
	isDead = false;
	weapons[0];
	teamNumber = 1;
	player = new Person;
	cameraHeight = 5.0f;
	crawlCameraHeight = 5.0f;
	teamColor = 1;
}


//Person::getStance(Stance iCanMove)
//{
//
//}

void Person::setStance(Stance iCanMove)
{

}
bool Person::getDeath()
{
	return isDead;
}
void Person::setDeath(bool isDead)
{

}
Weapon Person::getWeapon(){
	return weapons[10];
}
void Person::setWeapon(Weapon gunType){

}
int Person::getTeam(){
	return teamNumber;
}
void Person::setTeam(int team){
	
}
int Person::takeHit(int damage){

}
bool Person::fire(){
	return fire;
}


int Person::takeHit(int damage)
{
	int hit = damage;
	int placeholder=0; // is placeholder being equal to hit and or damages
	//Player.Health -= damage;
	return placeholder; //Player.Health
}

float Person::getCameraHeight(){
	return cameraHeight;
}
void Person::setCameraHeight(float newHeight){
	cameraHeight = newHeight;
}
float Person::getCrawlCameraHeight(){
	return crawlCameraHeight;
}
void  Person::setCrawlCameraHeight(float newHeight){
	crawlCameraHeight = newHeight;
}
int Person::getTeamColor(){
	return teamColor;
}
void Person::setTeamColor(int newColor){
	teamColor = newColor;
}
