#pragma once
#include "Object.h"
class World
{
public:
	void setObject(int index);
	void convert(int teamIndex, int objectIndex);
	

	World();
	~World();

private:

protected:
	Object* object;
	int numberTeams;
	Object Objects[10];
};

