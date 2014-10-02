#pragma once
#include "World.h"
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

