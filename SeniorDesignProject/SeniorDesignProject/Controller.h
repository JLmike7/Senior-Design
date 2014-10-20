#pragma once
#include "World.h"
#include "Biped.h"

class Controller :
	public World
{
public:
	Controller();
	~Controller();
	void beginMove(Direction direction);
	void look(Direction direction);
	void fire();
	void jump();
	void halt();
	void nextWeapon();
	void prevWeapon();
	void handleKey(char key);
private:
	bool movingFront;
	bool movingBack;
	bool movingLeft;
	bool movingRight;

protected:
	World* world;
	Biped* biped;
};