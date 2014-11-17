#ifndef ENEMY_H
#define ENEMY_H

#include "Stats.h"
#include "Position.h"
#include "WalkingStatus.h"


class Enemy : public Stats, Position{
public:
	Enemy(Point pos, Point lookat, Point up, int health, int kills, int deaths);
	~Enemy();


private:

};

#endif 