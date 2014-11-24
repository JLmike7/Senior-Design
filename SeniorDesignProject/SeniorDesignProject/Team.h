#ifndef TEAM_H
#define TEAM_H

#include "Biped.h"
#include "Friendly.h"
#include "Enemy.h"
#include<stdio.h>
#include<stdlib.h>

class Team {
public:
	Team(int numfriendly, int numEnemy);
	~Team();

private:
	int numfriendly;
	int numEnemy;

	// which sorting algorithm will be best used for a short list maybe
	// for about 10 or less in each list.
	//Friendly fri;
	//Enemy ene;



	/*void Init(Biped* members[MAX_MEMBERS],int memberCount,int teamNumber);
	void addMember(Biped* member,bool forceIntoTeam);
	Biped* getMember(int index);
	Biped** getMembers();

	Team(int teamNumber);
	Team::Team(Biped* _members[], int size, int teamNumber);
	~Team();

private:

protected:
	int teamNum;
	int memberCount;
	Biped* members[MAX_MEMBERS];*/
};

#endif