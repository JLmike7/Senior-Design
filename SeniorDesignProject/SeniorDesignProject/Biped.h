#pragma once
#include "Object.h"
#include "Weapon.h"
#include <deque>
#include "Position.h"
#include "Direction.h"
#include "Stats.h"
#include "Settings.h"
#include "Stance.h"

class Biped :
	public Object{

public:
	void Init(Settings *settings, Box *hitbox);
	Stance getStance();
	void setStance(Stance stance);
	void setHitbox(Box* box);
	Box* getHitbox();
	Weapon* getWeapon();
	void addWeapon(Weapon *newWeapon);
	void nextWeapon();
	void prevWeapon();
	int getTeam();
	void setTeam(int team);
	int takeHit(int damage);
	bool isDead();
	void beginMove(Direction direction);
	Position* getPosition();
	void fire();
	void jump();
	void lookTo(Direction direction);
	void lookAt(Point* point);

	Biped(Settings* settings, Box *hitbox);
	Biped();
	~Biped();

private:
	Settings*			settings;

protected:
	int					teamNumber;
	Stance				stance;
	Stats*				stats;
	std::deque<Weapon>*	weapons;
	Position*			position;
	Box*				hitbox;
};
