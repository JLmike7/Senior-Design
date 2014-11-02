#include "WalkingStatus.h"


WalkingStatus::WalkingStatus()
{
	walkingLeft = false;
	walkingRight = false;
	walkingForward = false;
	walkingBackward = false;
}


WalkingStatus::~WalkingStatus()
{
}

bool WalkingStatus::isWalking(Direction d){
	switch (d){
	case Direction::FRONT:
		return walkingForward;
		break;
	case Direction::BACK:
		return walkingBackward;
		break;
	case Direction::LEFT:
		return walkingLeft;
		break;
	case Direction::RIGHT:
		return walkingRight;
		break;
	}
}
void WalkingStatus::set(Direction d,bool startStop){
	switch (d){
	case Direction::FRONT:
		walkingForward = startStop;
		break;
	case Direction::BACK:
		walkingBackward = startStop;
		break;
	case Direction::LEFT:
		walkingLeft = startStop;
		break;
	case Direction::RIGHT:
		walkingRight = startStop;
		break;
	}
}