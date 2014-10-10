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
private:

protected:
	World* world;
	Biped* biped;
};