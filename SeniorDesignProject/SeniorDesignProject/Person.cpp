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
	this.isDead = isDead;
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
	this.team = team;
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
	this.health = newhealth;
}

int takeHit(int damage)
{
	int hit = damage;
	int placeholder=0; // is placeholder being equal to hit and or damages
	this.health -= damage;
	return placeholder; //Player.Health
}
