#ifndef STATS_H
#define STATS_H

#include "Definitions.h"

class Stats{
public:
	Stats(int _health, int _kills, int _deaths);
	~Stats();

	int getHealth();
	void setHealth(int currentHealth);
	int getkills();
	void setkills(int _kills);
	int getdeaths();
	void setdeaths(int _deaths);
	void regenerate();
	bool isDead();

private:
	int health;
	int kills;
	int deaths;
};

#endif