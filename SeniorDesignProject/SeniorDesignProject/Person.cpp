#include "Person.h"


Person::Person()
{

}


Person::~Person()
{
}

void Person::Init(int health)
{
	health = 100;
	isDead = false;
	weapons[0];
	teamNumber = 1;
	player = new Person;
	cameraHeight = 5.0f;
	crawlCameraHeight = 5.0f;
	teamColor = 1;
}

void Person::setStance(Stance iCanMove)
{

}
bool Person::getDeath()
{
	return isDead;
}
void Person::setDeath(bool isDeads)
{
	isDead = isDeads;
}
Weapon Person::getWeapon(){
	return weapons[10];
}
void Person::setWeapon(Weapon gunType){

}
int Person::getTeam(){
	return teamNumber;
}
void Person::setTeam(int teams){
	teamNumber = teams;
}
int Person::takeHit(int damage){

}
bool Person::fire(){
	return fire;
}

int Person::gethealth(){
	return health;
}

void Person::sethealth(int newhealth){
	health = newhealth;
}

int Person::takeHit(int damage)
{
	int hit = damage;
	int placeholder=0; // is placeholder being equal to hit and or damages
	health -= damage;
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
