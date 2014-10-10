#pragma once
#include "Object.h"
#include "Weapon.h"
#include <deque>
#include "Position.h"
#include "Direction.h"
#include "Stats.h"

class Biped :
	public Object{

enum Stance { RUN, WALK, CRAWL };

public:
	void Init(Settings *settings);
	Stance getStance();
	void setStance(Stance stance);
	Weapon* getWeapon();
	void pushWeapon(Weapon *newWeapon);
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
	Position* getPosition();
	void  setPosition(Position *position);
	void fire();
	void move(Direction direction);
	void jump();
	void lookTo(Direction direction);
	void lookAt(Point* point);
	Biped(Settings* settings);
	~Biped();

private:
	Settings*			settings;

protected:
	Stance				stance;
	std::deque<Weapon>*	weapons;
	int					teamNumber;
	float				cameraHeight;
	float				crawlCameraHeight;
	int					teamColor;
	bool				dead;
	Stats*				stats;
	Position*			position;
};
