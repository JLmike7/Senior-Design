#pragma once
#include "Direction.h"
class WalkingStatus
{
public:
	bool isWalking(Direction d);
	WalkingStatus();
	~WalkingStatus();
	void set(Direction d,bool startStop);
private:
	bool	walkingForward, walkingBackward, walkingLeft, walkingRight;
};

