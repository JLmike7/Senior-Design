#include "Weapon.h"

Weapon::Weapon()
{
	Init();
}


Weapon::~Weapon()
{
}

void Weapon::Init(){
	range = 10.0f; //Fire cone length
	spread = 2.0f; //Fire cone radius
	accuracy = 85.0f; //Fire cone random tilt
	attack = 20.0f;
	meleeAttack = 45.0f;
	defend = 10.0f;
	reloadTime = 2; //In milliseconds
	magSize = 8; //Magazine capacity
	extraMags = 3;
}
float Weapon::getRange()
{
	return range;
}
void Weapon::setRange(float Range){
	range = Range;
}
float Weapon::getSpread(){
	return spread;
}
void Weapon::setSpread(float Spread){
	spread = Spread;
}
float Weapon::getAccuracy(){
	return accuracy;
}
void Weapon::setAccuracy(float Accuracy){
	accuracy = Accuracy;
}
float Weapon::getAttack(){
	return attack;
}
void Weapon::setAttack(float attackDmg){
	attack = attackDmg;
}
float Weapon::getMelee(){
	return meleeAttack;
}
void Weapon::setMelee(float meleeDmg){
	meleeAttack = meleeDmg;
}
float Weapon::getDefend(){
	return defend;
}
void Weapon::setDefend(float defenceRating){
	defend = defenceRating;
}
int Weapon::getReloadTime(){
	return reloadTime;
}
void Weapon::setReloadTime(int ReloadTime){
	reloadTime = ReloadTime;
}
void Weapon::setExtraClips(int clips)
{
	extraMags += clips;
}
int Weapon::getExtraClips(){
	return extraMags;
}
int Weapon::getMagSize(){
	return magSize;
}
void Weapon::setMagSize(int MagSize){
	magSize = MagSize;
}
void Weapon::reload()
{
	if (getExtraClips() > 0)
	{
		setMagSize(8);
	}
}
