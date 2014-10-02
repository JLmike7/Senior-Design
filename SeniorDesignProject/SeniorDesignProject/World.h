#pragma once
#include "Person.h"
class World
{
public:
	void Init();
	void setPlayer(int index);
	void convert(int personIndex);
	Person* getPlayer();
	Person* getPerson(int index);
	Person** getTeam(int teamIndex, bool aliveOnly);
	int getTeamSize(int teamIndex, bool aliveOnly);
	Person** getTeams(bool aliveOnly);
	

	World();
	~World();

private:

protected:
	Person* player;
	int numberTeams;
	Person people[10];
};
