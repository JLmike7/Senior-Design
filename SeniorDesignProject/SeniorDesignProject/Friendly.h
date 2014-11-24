#ifndef FRIENDLY_H
#define FRIENDLY_H

#include "Stats.h"
#include "Position.h"
#include "WalkingStatus.h"

class Friendly : public Stats, Position{
public:
	Friendly(Point pos, Point lookat, Point up, int health, int kills, int deaths);
	~Friendly();
private:

};

#endif