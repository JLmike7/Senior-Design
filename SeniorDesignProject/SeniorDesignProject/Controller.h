#pragma once
#include "World.h"
#include "Biped.h"

class Controller :
	public World
{
public:
	Controller();
	~Controller();
	void fire();
	void jump();
	void halt();
	void nextWeapon();
	void prevWeapon();
	void handleKeyDown(char key);
	void handleKeyUp(char key);
private:
	bool movingFront;
	bool movingBack;
	bool movingLeft;
	bool movingRight;

protected:
	World* world;
	Biped* biped;
};