#pragma once
#include "World.h"

World::World()
{

}


World::~World()
{

}

void World::Init(){
	/*physics = new Physics();
	settings = new Settings();
	playerIndex = -1;
	for (int team = 0; team < NUMBER_TEAMS; team++){
		for (int teamBipedIndex = 0; teamBipedIndex < TEAM_SIZE; teamBipedIndex++){
			int i = (team*TEAM_SIZE) + teamBipedIndex;
			people[i] = new Biped(settings);
			//First biped on friendly team is the player
			if (playerIndex == -1 && team == FRIENDLY_TEAM){
				setPlayer(i);
			}
			people[i]->setTeam(team);
			physics->enableGravity(people[i]->getPosition());
		}
	}*/
}

void World::tick(){
	//Tick all players then all gravity-enabled objects
	/*for (int b = 0; b < TEAM_SIZE*NUMBER_TEAMS; b++){
		//people[b]->getPosition()->applyTickMovement(1);
		people[b]->getPosition()->applyTickMovement();
		physics->applyGroundPushback(people[b]->getPosition());
		
	}
	*/
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
	return people[playerIndex];
}
Biped* World::getBiped(int index)
{
	return people[index];
}

//This method is inneficient.  Use sparingly.
Team* World::getTeam(int teamNum, bool aliveOnly){
	Team* team = new Team(teamNum, teamNum);
	//for each player, put them in the team object
	/*for (int i = 0; i < TEAM_SIZE*NUMBER_TEAMS; i++){
		if (!aliveOnly || !people[i]->getDeath()){
			team->addMember(people[i], false);
		}
	}*/
	return team;
}
//This method is inneficient.  Use sparingly.
int World::getTeamSize(int teamNum, bool aliveOnly){
	int peopleInTeam = 0;
	/*for (int i = 0; i < TEAM_SIZE*NUMBER_TEAMS; i++){
		if (people[i]->getTeam() == teamNum && (!aliveOnly || people[i]->getDeath())){
			peopleInTeam++;
		}
	}*/
	return peopleInTeam;
}

//Divides the players by team
Team** World::getTeams(bool aliveOnly){
	//Initialize teams
	Team* teams[NUMBER_TEAMS];
	/*for (int i = 0; i < NUMBER_TEAMS; i++){
		teams[i] = new Team(i);
	}
	//for each player, put them in their team object
	for (int i = 0; i < TEAM_SIZE*NUMBER_TEAMS; i++){
		if (!aliveOnly || !people[i]->getDeath()){
			teams[people[i]->getTeam()]->addMember(people[i],false);
		}
	}*/
	return teams;
}
void World::convert(int BipedIndex)
{
	//people[BipedIndex].setTeam(FRIENDLY_TEAM);
}