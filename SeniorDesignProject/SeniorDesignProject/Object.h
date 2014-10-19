#pragma once
#include "Position.h"
#include "Box.h"

class Object
{
public:
	void Init(Box hitbox);
	bool getDeath();
	void setDeath(bool isDead);
	void setGravityEnabled(bool gravity);
	bool isGravityEnabled();

	Position* getPosition();
	void  setPosition(Position *position);

	Object(Box hitbox);
	Object();
	~Object();

private:


protected:
	Position*	position;
	bool		isDead;
	Box			hitbox;
	bool		gravityEnabled;
};

