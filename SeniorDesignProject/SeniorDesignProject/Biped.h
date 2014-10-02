#pragma once
#include "Object.h"
#include "Weapon.h"
class Biped :
	public Object
{
public:
	void Init();
	//Stance getStance();
	//void setStance(Stance iCanMove);
	Weapon getWeapon();
	void setWeapon(Weapon gunType);
	int getTeam();
	void setTeam(int team);
	int takeHit(int damage);
	bool fire();
	float getCameraHeight();
	void setCameraHeight(float newHeight);
	float getCrawlCameraHeight();
	void  setCrawlCameraHeight(float newHeight);
	int getTeamColor();
	void setTeamColor(int newColor);

	Biped();
	~Biped();

private:


protected:

	Weapon		weapons;
	int			teamNumber;
	Biped*		biped;
	float		cameraHeight;
	float		crawlCameraHeight;
	int			teamColor;
};
