#pragma once
#include "Object.h"
#include "Weapon.h"
#include <deque>
#include "Position.h"
#include "Direction.h"
#include "Stats.h"
#include "Settings.h"
#include "Stance.h"
#include "WalkingStatus.h"



class Biped : public Stats, public Position{
public:
	Biped(Point pos, Point lookat, Point up, int health, int kills, int deaths);
	Biped(int health, int kills, int deaths);
	~Biped();
	
	Stance getStance();
	void setStance(Stance stance);
	Weapon* getWeapon();
	void addWeapon(Weapon *newWeapon);
	void nextWeapon();
	void prevWeapon();
	void fire();
	
	//void Init(Settings *settings);
	//void takeHit(int damage);
	//void beginMove(Direction direction);
	//void jump();
	//void lookTo(Direction direction);
	//void lookAt(Point* point,bool tracking);
	//void walk(Direction direction,bool startStop);
	//void setDeath(bool isDead);

private:

protected:
	//Settings*			settings;
	int					teamNumber;
	Stance				stance;
	std::deque<Weapon>*	weapons;
	WalkingStatus*		walkingStatus;

	//Collision			box;
};
