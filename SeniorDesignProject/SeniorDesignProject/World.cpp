#pragma once
#include "World.h"

World::World()
{

}


World::~World()
{

}

void World::Init(){
	physics = new Physics();
	playerIndex = -1;
	for (int team = 0; team < NUMBER_TEAMS; team++){
		for (int teamBipedIndex = 0; teamBipedIndex < TEAM_SIZE; teamBipedIndex++){
			int i = (team*TEAM_SIZE) + teamBipedIndex;
			if (playerIndex == -1 && team == FRIENDLY_TEAM){
				setPlayer(i);
			}
			bipeds[i]->setTeam(team);
			physics->enableGravity(bipeds[i]->getPosition());
		}
	}
}

void World::tick(){
	//Tick all players then all objects
	for (int b = 0; b < TEAM_SIZE*NUMBER_TEAMS; b++){
		bipeds[b]->getPosition()->applyTickMovement();
		physics->applyGroundPushback(bipeds[b]->getPosition());
	}

//TODO: finish object gravity.  Ticking 1024 objects per frame is bad.

//	for (int o = 0; o < MAX_OBJECTS; o++){
//		objects[o]->getPosition()->applyTickMovement();
//		physics->applyGroundPushback(objects[o]->getPosition());
//	}
}

void World::setPlayer(int index)
{
	playerIndex = index;
}

Biped* World::getPlayer()
{
	return bipeds[playerIndex];
}
Biped* World::getBiped(int index)
{
	return bipeds[index];
}

//This method is inneficient.  Use sparingly.
Team* World::getTeam(int teamNum, bool aliveOnly){
	Team* team = new Team(teamNum);
	//for each player, put them in the team object
	for (int i = 0; i < TEAM_SIZE*NUMBER_TEAMS; i++){
		if (!aliveOnly || !bipeds[i]->getDeath()){
			team->addMember(bipeds[i], false);
		}
	}
}
//This method is inneficient.  Use sparingly.
int World::getTeamSize(int teamNum, bool aliveOnly){
	int peopleInTeam = 0;
	for (int i = 0; i < TEAM_SIZE*NUMBER_TEAMS; i++){
		if (bipeds[i]->getTeam() == teamNum && (!aliveOnly || bipeds[i]->getDeath())){
			peopleInTeam++;
		}
	}
	return peopleInTeam;
}

//Divides the players by team
Team** World::getTeams(bool aliveOnly){
	//Initialize teams
	Team* teams[NUMBER_TEAMS];
	for (int i = 0; i < NUMBER_TEAMS; i++){
		teams[i] = new Team(i);
	}
	//for each player, put them in their team object
	for (int i = 0; i < TEAM_SIZE*NUMBER_TEAMS; i++){
		if (!aliveOnly || !bipeds[i]->getDeath()){
			teams[bipeds[i]->getTeam()]->addMember(bipeds[i],false);
		}
	}
	return teams;
}
void World::convert(int BipedIndex)
{
	bipeds[BipedIndex]->setTeam(FRIENDLY_TEAM);
}