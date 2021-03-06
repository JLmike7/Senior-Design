#pragma once
#include "World.h"
#include "Biped.h"
#include "Direction.h"

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
	void handleKey(char key);
	void look(Direction direction);
private:
	bool movingFront;
	bool movingBack;
	bool movingLeft;
	bool movingRight;

protected:
	World* world;
	Biped* biped;
};