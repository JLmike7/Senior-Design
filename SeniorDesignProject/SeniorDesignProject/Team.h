#pragma once
#include "Biped.h"

#define MAX_MEMBERS 20

class Team
{
public:
	void Init(Biped* members[MAX_MEMBERS],int memberCount);
	void addMember(Biped* member);
	Biped* getMember(int index);
	Biped** getMembers();

	Team();
	~Team();

private:

protected:
	int memberCount;
	Biped* members[MAX_MEMBERS];
};