#pragma once
#include "World.h"
#include "Position.h"
#include "Stats.h"
#include "Biped.h"

class Object :
	public World
{
public:
	void Init();
	bool getDeath();
	void setDeath(bool isDead);

	Object();
	~Object();

private:


protected:

	bool		isDead;
};

