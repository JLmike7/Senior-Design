#include "Team.h"

Team::Team(int numfriendly, int numEnemy){
	// this is where we will declare the two lists
}

Team::~Team(){

}

/*
Team::Team(int teamNumber)
{
	Init({}, 0, teamNumber);
}

Team::Team(Biped* _members[], int size, int teamNumber)
{
	Init(_members, size, teamNumber);
}

Team::~Team()
{

}

void Team::Init(Biped* _members[],int size,int teamNumber){
	teamNum = teamNumber;
	for (int i = 0; i < size; i++){
		addMember(_members[i],false);
	}
}

void Team::addMember(Biped* member,bool forceIntoTeam){
	if (memberCount <= MAX_MEMBERS){
		if (forceIntoTeam){
			member->setTeam(teamNum);
		}
		if (member->getTeam() == teamNum){
			members[memberCount] = member;
			memberCount++;
		}
		else{
			//TODO: throw an error, player doesn't belong in this team!
		}
	}
	else{
		//TODO: Make error for "not enough room"!
	}
}

Biped* Team::getMember(int index){
	return members[index];
}

Biped** Team::getMembers(){
	return members;
}*/