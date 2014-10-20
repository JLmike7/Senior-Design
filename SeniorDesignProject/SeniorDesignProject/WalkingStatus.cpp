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
void WalkingStatus::setTrue(Direction d){
	switch (d){
	case Direction::FRONT:
		walkingForward=true;
		break;
	case Direction::BACK:
		walkingBackward = true;
		break;
	case Direction::LEFT:
		walkingLeft = true;
		break;
	case Direction::RIGHT:
		walkingRight = true;
		break;
	}
}
void WalkingStatus::setFalse(Direction d){
	switch (d){
	case Direction::FRONT:
		walkingForward = true;
		break;
	case Direction::BACK:
		walkingBackward = true;
		break;
	case Direction::LEFT:
		walkingLeft = true;
		break;
	case Direction::RIGHT:
		walkingRight = true;
		break;
	}
}