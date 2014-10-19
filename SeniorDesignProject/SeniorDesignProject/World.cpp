#pragma once
#include "World.h"

World::World()
{

}


World::~World()
{

}

void World::Init(){
	playerIndex = -1;
	for (int team = 0; team < NUMBER_TEAMS; team++){
		for (int Biped = 0; Biped < TEAM_SIZE; Biped++){
			int i = team*TEAM_SIZE + Biped;
			if (playerIndex == -1 && team == FRIENDLY_TEAM){
				playerIndex = i;
			}
			people[i].setTeam(team);
		}
	}
}

void World::setPlayer(int index)
{
	playerIndex = index;
}


//This method is inneficient.  Use sparingly.
/*Biped** World::getTeam(int teamNum, bool aliveOnly){
	//Create a new array of Biped pointers.
	//Copy from people[] to team[] if teamIndex matches.

}*/
//This method is inneficient.  Use sparingly.
int World::getTeamSize(int teamNum, bool aliveOnly){
	int peopleInTeam = 0;
	for (int i = 0; i < TEAM_SIZE*NUMBER_TEAMS; i++){
		if (people[i].getTeam() == teamNum && (!aliveOnly || people[i].getDeath())){
			peopleInTeam++;
		}
	}
	return peopleInTeam;
}

//Divides the players by team
/*Biped** World::getTeams(bool aliveOnly){
	//Team size must be able to include all players, in the case that a player converted everyone to their team.
	Biped* teams[NUMBER_TEAMS][TEAM_SIZE*NUMBER_TEAMS];
	int teamCounts[NUMBER_TEAMS];
	//set all teamCounts to zero
	for (int i = 0; i < NUMBER_TEAMS; i++)
		teamCounts[i] = 0;
	//for each player, put them in an array in teams.
	for (int i = 0; i < TEAM_SIZE*NUMBER_TEAMS; i++){
		if (!aliveOnly || people[i].getDeath()){
			int teamNum = people[i].getTeam();
			teams[teamNum][teamCounts[teamNum]] = &people[i];
			teamCounts[teamNum]++;
		}
	}
	return teams;
}*/
void World::convert(int BipedIndex)
{
	people[BipedIndex].setTeam(FRIENDLY_TEAM);
}