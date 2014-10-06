#pragma once
#include "Position.h"

class Object
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

