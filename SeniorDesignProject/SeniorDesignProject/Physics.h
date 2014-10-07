#pragma once
class Physics
{

public:
	
	void Init();
	double getGravity();  //I don't think you understand the gravity of this situation
	void setGravity(double newGravity);
	double getWind();
	void setWind(double newWind);
	float getGroundHeight();
	void setGroundHeight(float newHeight);
	float getWaterChoppiness();
	void setWaterChoppiness(float newChoppiness); //I think this is a word but it looks wrong...oh well. 
	Physics();
	~Physics();

private:

protected:
	double gravity;
	double wind;
	float groundHeight;
	float waterChoppiness;

	
};

