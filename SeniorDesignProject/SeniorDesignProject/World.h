#pragma once
#include "Person.h"

#define TEAM_SIZE 5
#define NUMBER_TEAMS 2
#define FRIENDLY_TEAM 0

class World
{
public:
	void Init();
	void setPlayer(int index);
	void convert(int BipedIndex);
	Biped* getPlayer();
	Biped* getBiped(int index);
	//Biped** getTeam(int teamIndex, bool aliveOnly);
	int getTeamSize(int teamIndex, bool aliveOnly);
	//Biped** getTeams(bool aliveOnly);


	World();
	~World();

private:

protected:
	int playerIndex;
	Person* people[TEAM_SIZE*NUMBER_TEAMS];
};