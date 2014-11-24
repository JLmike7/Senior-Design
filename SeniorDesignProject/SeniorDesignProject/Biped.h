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

#define HIT_BOX_WIDTH 0.75f
#define HIT_BOX_HEIGHT 2.0f
#define HIT_BOX_DEPTH 0.75f


class Biped :
	public Object{

public:
	void Init(Settings *settings);
	Stance getStance();
	void setStance(Stance stance);
	//	void setHitbox(Box* box);
	//	Box* getHitbox();
	Weapon* getWeapon();
	void addWeapon(Weapon *newWeapon);
	void nextWeapon();
	void prevWeapon();
	int getTeam();
	void setTeam(int team);
	void takeHit(int damage);
	bool isDead();
	void beginMove(Direction direction);
	Position* getPosition();
	void fire();
	void jump();
	void lookTo(Direction direction);
	void lookAt(Point* point, bool tracking);
	void walk(Direction direction, bool startStop);
	bool getDeath();
	void setDeath(bool isDead);

	Biped(Settings* settings);
	Biped();
	~Biped();

private:

protected:
	Settings*			settings;
	int					teamNumber;
	Stance				stance;
	Stats*				stats;
	std::deque<Weapon>*	weapons;
	Position*			position;
	//	Box*				hitbox;
	WalkingStatus*		walkingStatus;
	bool				death;
};
