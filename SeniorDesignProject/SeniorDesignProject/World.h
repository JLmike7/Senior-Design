#pragma once
#include "Biped.h"
#include "Physics.h"
class World
{
public:
	void setPlayer(int index);
	void convert(int teamIndex, int personIndex);
	

	World();
	~World();

private:

protected:
	Biped* player;
	int numberTeams;
	Biped people[10];
};
