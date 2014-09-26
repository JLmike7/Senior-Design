#pragma once
#include "World.h"
class Physics : 
	public World
{
public:
	void Init();
	float getGravity();  //I don't think you understand the gravity of this situation
	void setGravity(float newGravity);
	float getWind();
	void setWind(float newWind);
	float getGroundHeight();
	void setGroundHeight(float newHeight);
	float getWaterChoppiness();
	void setWaterChoppiness(float newChoppiness); //I think this is a word but it looks wrong...oh well. 
	Physics();
	~Physics();

private:

protected:
	float gravity;
	float wind;
	float groundHeight;
	float waterChoppiness;
};

