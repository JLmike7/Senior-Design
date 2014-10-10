#include "Biped.h"
#include "Stats.h"

Biped::Biped()
{
	Init();
}


Biped::~Biped()
{
}

void Biped::Init()
{
	stance = walk;
	teamNumber = 1;
	cameraHeight = 5.0f;
	crawlCameraHeight = 5.0f;
	teamColor = 1;
}


Biped::Stance Biped::getStance()
{
	return stance;
}

void Biped::setStance(Stance stance)
{
	Biped::stance = stance;
}

Weapon Biped::getWeapon(){
	return weapons.front();
}
void Biped::pushWeapon(Weapon newWeapon){
	weapons.push_front(newWeapon);
}
int Biped::getTeam(){
	return teamNumber;
}
void Biped::nextWeapon(){
	weapons.push_back(weapons.front());
	weapons.pop_front();
}
void Biped::prevWeapon(){
	weapons.push_front(weapons.back());
	weapons.pop_back();
}
void Biped::setTeam(int _team){
	teamNumber = _team;
}
int Biped::takeHit(int damage){
	stats.setHealth(stats.getHealth()-damage);
}
void Biped::fire(){
	//TODO: implement
}


int Biped::takeHit(int damage)
{
	int hit = damage;
	int placeholder=0; // is placeholder being equal to hit and or damages
	//biped.Health -= damage;
	Stats myStats;
	//myStats.setHealth(myStats.getHealth =- damage);
	return 90; //biped.Health
}

float Biped::getCameraHeight(){
	return cameraHeight;
}
void Biped::setCameraHeight(float newHeight){
	cameraHeight = newHeight;
}
float Biped::getCrawlCameraHeight(){
	return crawlCameraHeight;
}
void  Biped::setCrawlCameraHeight(float newHeight){
	crawlCameraHeight = newHeight;
}
int Biped::getTeamColor(){
	return teamColor;
}
void Biped::setTeamColor(int newColor){
	teamColor = newColor;
}
bool Biped::getDeath(){
	return dead;
}
void Biped::setDeath(bool isDead){
	dead = isDead;
}
