#pragma once
#include "World.h"
class Controller :
	public World
{
public:
	Controller();
	~Controller();
private:

protected:
	World* world;

};

