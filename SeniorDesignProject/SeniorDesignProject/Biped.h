#pragma once
#include "Object.h"
#include "Weapon.h"
#include <deque>
class Biped :
	public Object{

enum Stance { sprint, walk, crouch };

public:
	void Init();
	Stance getStance();
	void setStance(Stance stance);
	Weapon getWeapon();
	void pushWeapon(Weapon gunType);
	void nextWeapon();
	void prevWeapon();
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
	void fire();
	Biped();
	~Biped();

private:


protected:
	Stance				stance;
	std::deque<Weapon>	weapons;
	int					teamNumber;
	float				cameraHeight;
	float				crawlCameraHeight;
	int					teamColor;
	bool				dead;
	Stats				stats;
};
