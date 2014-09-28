#pragma once
#include "World.h"
#include "Stance.h"
#include "Weapon.h"
class Person :
	public World
{
public:
	void Init(int health);
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
	int gethealth();
	void sethealth();
	Person();
	~Person();

	enum Stances
	{
		STATIONARY,
		RUNNING,
		WALKING,
		CRAWLING
	};

private:


protected:

	bool		isDead;
	Weapon		weapons[10];
	int			teamNumber;
	int			health;
};
