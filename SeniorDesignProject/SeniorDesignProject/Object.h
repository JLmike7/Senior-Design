#pragma once
#include "Position.h"

class Object
{
public:
	void Init();
	bool getDeath();
	void setDeath(bool isDead);
	void setGravityEnabled(bool gravity);
	bool isGravityEnabled();

	Position* getPosition();
	void  setPosition(Position *position);

	Object();

	~Object();

private:


protected:
	Position*	position;
	bool		isDead;
	//	Box			hitbox;
	bool		gravityEnabled;
};

