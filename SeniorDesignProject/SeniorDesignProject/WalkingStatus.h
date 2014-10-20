#pragma once
#include "Direction.h"
class WalkingStatus
{
public:
	bool isWalking(Direction d);
	WalkingStatus();
	~WalkingStatus();
	void setTrue(Direction d);
	void setFalse(Direction d);
private:
	bool	walkingForward, walkingBackward, walkingLeft, walkingRight;
};

