#pragma once
#include "World.h"
#include "Stance.h"
#include "Weapon.h"
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
	void setWeapon(Weapon gunType);
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
