#pragma once
#include "World.h"
class Person :
	public World
{
public:
	//Stance stance;
	bool			isDead;
	//Weapon[n] weapons;
	int				teamNumber;
	Person();
	~Person();

private:


protected:
};
