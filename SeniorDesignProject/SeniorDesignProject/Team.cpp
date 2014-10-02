#pragma once
#include "Team.h"

Team::Team()
{

}


Team::~Team()
{

}

void Team::Init(Person* _members[],int size){
	if (memberCount <= MAX_MEMBERS){
		for (int i = 0; i < size; i++){
			addMember(_members[i]);
		}
	}
}

void Team::addMember(Person* member){
	members[memberCount] = member;
	memberCount++;
}

Person* Team::getMember(int index){
	return members[index];
}

Person** Team::getMembers(){
	return members;
}