#pragma once
#include "Biped.h"
#include "Team.h"
#include "Physics.h"
#include "Settings.h"

#define TEAM_SIZE 5
#define NUMBER_TEAMS 2
#define FRIENDLY_TEAM 0
#define MAX_OBJECTS 1024

class World
{
public:
	void Init();
	void setPlayer(int index);
	void convert(int BipedIndex);
	Biped* getPlayer();
	Biped* getBiped(int index);
	Team* getTeam(int teamIndex, bool aliveOnly);
	int getTeamSize(int teamIndex, bool aliveOnly);
	Team** getTeams(bool aliveOnly);
	void tick();


	World();
	~World();

private:

protected:
	int playerIndex;
	Biped* bipeds[TEAM_SIZE*NUMBER_TEAMS];
	Physics* physics;
	Object* objects[MAX_OBJECTS];
	Settings* settings;
};