#include "Weapon.h"

Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

void Weapon::Init(){
	range = 10.0; //Fire cone length
	spread = 2.0; //Fire cone radius
	accuracy = 85.0; //Fire cone random tilt
	attack = 20.0;
	meleeAttack = 45.0;
	defend = 10.0;
	reloadTime = 2; //In milliseconds
	magSize = 8; //Magazine capacity
}
float Weapon::getRange()
{
	return range;
}
void Weapon::setRange(float Range){

}
float Weapon::getSpread(){
	return spread;
}
void Weapon::setSpread(float spread){

}
float Weapon::getAccuracy(){
	return accuracy;
}
void Weapon::setAccuracy(float accuracy){

}
float Weapon::getAttack(){
	return attack;
}
void Weapon::setAttack(float attackDmg){

}
float Weapon::getMelee(){
	return meleeAttack;
}
void Weapon::setMelee(float meleeDmg){

}
float Weapon::getDefend(){
	return defend;
}
void Weapon::setDefend(float defenceRating){

}
int Weapon::getReloadTime(){
	return reloadTime;
}
void Weapon::setReloadTime(int reloadTime){

}
int Weapon::getMagSize(){
	return magSize;
}
void Weapon::setMagSize(int magSize){

}
