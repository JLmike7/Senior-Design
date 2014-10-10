#pragma once
#include "Biped.h"

#define MAX_MEMBERS 20

class Team
{
public:
	void Init(Biped* members[MAX_MEMBERS],int memberCount,int teamNumber);
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
	Biped* members[MAX_MEMBERS];
};