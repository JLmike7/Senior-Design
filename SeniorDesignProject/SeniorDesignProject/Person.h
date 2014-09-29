#pragma once
#include "World.h"
#include "Stance.h"
#include "Weapon.h"
#include <queue>

#define MAX_WEAPONS 10
#define MAX_HEALTH 100
#define MELEE_ATTACK 10

class Person :
	public World
{
public:
	void Init();
	Stance getStance();
	void setStance(Stance iCanMove);
	bool getDeath();
	void setDeath(bool isDead);
	Weapon getWeapon();
	void pushWeapon(Weapon _weapon);
	void popWeapon();
	void setActiveWeapon(int index);
	int getTeam();
	void setTeam(int team);
	int takeHit(int damage);
	bool fire();

	Person();
	~Person();



private:


protected:

	Stance		stance;
	bool		isDead;
	Weapon		weapons[10];
	int			teamNumber;
};
