#pragma once
#include "Object.h"
#include "Weapon.h"
class Biped :
	public Object
{
public:
	void Init();
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
	bool fire();

	Biped();
	~Biped();

private:


protected:

	Weapon		weapons[10];
	int			teamNumber;
	float		cameraHeight;
	float		crawlCameraHeight;
	int			teamColor;
	bool		fire;
	bool		death;
};
