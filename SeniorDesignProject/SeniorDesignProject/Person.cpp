#include "Person.h"

Person::Person()
{

}


Person::~Person()
{

}

void Person::Init(int teamNum)
{
	health = MAX_HEALTH;
	stance = STATIONARY;
	weapons[MAX_WEAPONS];
	teamNumber = teamNum;
}

Stance Person::getStance()
{
	return stance;
}

void Person::setStance(Stance _stance)
{
	stance = _stance;
}
bool Person::getDeath()
{
	return health < 1;
}
Weapon Person::getWeapon(){
	return weapons.front();
}
void Person::pushWeapon(Weapon _weapon){
	weapons.push(_weapon);
}
void Person::popWeapon(){
	return weapons.pop();
}
int Person::getTeam(){
	return teamNumber;
}
void Person::setTeam(int team){
	teamNumber = team;
}
void Person::takeHit(int damage){
	health -= damage;
}
int Person::getWeaponAttack(){
	return getWeapon().getAttack();
}
int Person::getMeleeAttack(){
	return MELEE_ATTACK;
}


//int takeHit(int damage)
//{
//	int hit = damage;
//	int placeholder=0; // is placeholder being equal to hit and or damages
	//Player.Health -= damage;
//	return placeholder; //Player.Health
//}
