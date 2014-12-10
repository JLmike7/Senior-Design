#pragma once
#include "Object.h"
#include "Weapon.h"
#include <deque>
#include "Position.h"
#include "Direction.h"
#include "Stats.h"
#include "Stance.h"
#include "WalkingStatus.h"

#define HIT_BOX_WIDTH 0.75f
#define HIT_BOX_HEIGHT 2.0f
#define HIT_BOX_DEPTH 0.75f


class Biped {

public:
	void Init();
	// Stance getStance();
	// void setStance(Stance stance);
	// void setHitbox(Box* box);
	// Box* getHitbox();
	// Weapon* getWeapon();
	// void addWeapon(Weapon *newWeapon);
	// void nextWeapon();
	// void prevWeapon();
	int getTeam();
	void setTeam(int team);
	// void takeHit(int damage);
	// void beginMove(Direction direction);
	// Position* getPosition();
	// void jump();
	// void lookAt(Point* point, bool tracking);
	// void walk(Direction direction, bool startStop);
	bool getDeath();
	void setDeath(bool isDead);

	Biped();
	~Biped();

private:

protected:
	int					teamNumber;
	// Stance				stance;
	Stats*				stats;
	// std::deque<Weapon>*	weapons;
	Position*			position;
	//	Box*				hitbox;
	// WalkingStatus*		walkingStatus;
	bool				death;
};
