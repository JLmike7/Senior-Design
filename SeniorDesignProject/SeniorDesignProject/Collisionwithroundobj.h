#ifndef COLLISIONWITHROUNDOBJ_H
#define COLLISIONWITHROUNDOBJ_H

#include "Location.h"
#include <math.h>
#include "Collision.h"
#include "TriangleCollision.h"

class TriangleCollision;
class Collision;

class RoundCollision{
public:
	RoundCollision();
	RoundCollision(Location loc, float height, float raduis);
	~RoundCollision();

	bool checkPointCollision(Location other);
	bool checkAABBCollision(Collision other);
	bool checkSphereCollision(RoundCollision other);
	bool checkTriCollision(TriangleCollision other);
	Location getLocation();
	void setLocation(Location _loc);
	float getheight();
	void setheight(float height);
	float getraduis();
	void setraduis(float raduis);

private:
	Location loc;
	float height;
	float raduis;
};

#endif