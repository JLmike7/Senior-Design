#pragma once
#include "Position.h"
class Physics
{
public:
	
	void Init();
	double getWind();
	void setWind(double newWind);
	float getGroundHeight();
	void setGroundHeight(float newHeight);
	void enableGravity(Position* pos);
	void applyGroundPushback(Position* pos);
	Physics();
	~Physics();

private:

protected:
	double wind;
	float groundHeight;
};

