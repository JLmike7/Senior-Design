#pragma once
#include "Person.h"

#define MAX_MEMBERS 20

class Team
{
public:
	void Init(Person* members[MAX_MEMBERS],int memberCount);
	void addMember(Person* member);
	Person* getMember(int index);
	Person** getMembers();

	Team();
	~Team();

private:

protected:
	int memberCount;
	Person* members[MAX_MEMBERS];
};