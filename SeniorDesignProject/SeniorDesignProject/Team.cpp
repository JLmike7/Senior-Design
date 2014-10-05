#pragma once
#include "Team.h"

Team::Team()
{

}


Team::~Team()
{

}

void Team::Init(Biped* _members[],int size){
	if (memberCount <= MAX_MEMBERS){
		for (int i = 0; i < size; i++){
			addMember(_members[i]);
		}
	}
}

void Team::addMember(Biped* member){
	members[memberCount] = member;
	memberCount++;
}

Biped* Team::getMember(int index){
	return members[index];
}

Biped** Team::getMembers(){
	return members;
}