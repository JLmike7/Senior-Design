#pragma once
#include "Object.h"
#include "Stance.h"
#include "Weapon.h"
class Biped :
	public Object
{
public:
	void Init();
	Stance getStance();
	void setStance(Stance iCanMove);
	//Weapon getWeapon();
	//void setWeapon(Weapon gunType);
	int getTeam();
	void setTeam(int team);
	int takeHit(int damage);
	bool firing();
	float getCameraHeight();
	void setCameraHeight(float newHeight);
	float getCrawlCameraHeight();
	void  setCrawlCameraHeight(float newHeight);
	int getTeamColor();
	void setTeamColor(int newColor);
	bool getDeath();
	void setDeath(bool isDead);

	Biped();
	~Biped();

private:


protected:

	Stance		stance;
	Weapon		weapons[10];
	int			teamNumber;
	float		cameraHeight;
	float		crawlCameraHeight;
	int			teamColor;
};
