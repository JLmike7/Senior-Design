#pragma once
#include "Person.h"
class World
{
public:
	void setPlayer(int index);
	void convert(int teamIndex, int personIndex);
	

	World();
	~World();

private:

protected:
	Person* player;
	int numberTeams;
	Person people[10];
};

