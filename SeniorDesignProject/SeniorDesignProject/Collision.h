#ifndef COLLISION_H
#define COLLISION_H

#include "Location.h"
#include <math.h>
#include "Collisionwithroundobj.h"
#include "TriangleCollision.h"

class TriangleCollision;
class RoundCollision;

class Collision{
public:
	Collision();
	Collision(Location _loc, float _height, float _length, float _width);
	~Collision();

	bool checkPointCollision(Location other);
	bool checkAABBCollision(Collision other);
	bool checkRoundCollision(RoundCollision other);
	bool checkTriCollision(TriangleCollision other);
	Location newLocation(float height);
	Location getLocation();
	void setLocation(Location _loc);
	float getheight();
	void setheight(float _height);
	float getlength();
	void setlength(float _length);
	float getwidth();
	void setwidth(float _width);
private:
	Location loc;
	float height;
	float length;
	float width;
};

#endif