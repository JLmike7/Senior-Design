#pragma once
#include "Biped.h"
#define NUMBER_TEAMS 2
#define TEAM_SIZE 2
#define FRIENDLY_TEAM 2
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
	Biped* player;
	int numberTeams;
	Biped people[10];
	int playerIndex;
};
