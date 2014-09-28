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
		for (int person = 0; person < TEAM_SIZE; person++){
			int i = team*TEAM_SIZE + person;
			if (playerIndex == -1 && team == FRIENDLY_TEAM){
				playerIndex = i;
			}
			people[i] = new Person;
			people[i]->setTeam(team);
		}
	}
}

void World::setPlayer(int index)
{
	playerIndex = index;
}

Person* World::getPlayer()
{
	return people[playerIndex];
}
Person* World::getPerson(int index)
{
	return people[index];
}

//This method is inneficient.  Use sparingly.
Person** World::getTeam(int teamNum,bool aliveOnly){
	//Create a new array of person pointers.
	//Copy from people[] to team[] if teamIndex matches.
	Person *team[TEAM_SIZE*NUMBER_TEAMS];
	int peopleInTeam = 0;
	for (int i = 0; i < TEAM_SIZE*NUMBER_TEAMS; i++){
		if (people[i]->getTeam() == teamNum && (!aliveOnly || people[i]->getDeath())){
			team[peopleInTeam] = people[i];
			peopleInTeam++;
		}
	}
	return team;
}
//This method is inneficient.  Use sparingly.
int World::getTeamSize(int teamNum, bool aliveOnly){
	int peopleInTeam = 0;
	for (int i = 0; i < TEAM_SIZE*NUMBER_TEAMS; i++){
		if (people[i]->getTeam() == teamNum && (!aliveOnly || people[i]->getDeath())){
			peopleInTeam++;
		}
	}
	return peopleInTeam;
}
void World::convert(int personIndex)
{
	people[personIndex]->setTeam(FRIENDLY_TEAM);
}