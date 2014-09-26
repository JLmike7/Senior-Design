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

}
void Person::setTeam(int team){

}
int Person::takeHit(int damage){

}
bool Person::fire(){

}


int takeHit(int damage)
{
	int hit = damage;
	int placeholder;
	//Player.Health -= damage;
	return placeholder; //Player.Health
}
