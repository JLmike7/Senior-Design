#pragma once
#include "World.h"
#include "Biped.h"

class Controller :
	public World
{
public:
	Controller();
	~Controller();
	void move(Direction direction);
	void look(Direction direction);
	void fire();
	void jump();
	void nextWeapon();
	void prevWeapon();
	void handleKeyPress(char key);
private:

protected:
	World* world;
	Biped* biped;
};