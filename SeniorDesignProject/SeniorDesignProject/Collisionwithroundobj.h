#ifndef COLLISIONWITHROUNDOBJ_H
#define COLLISIONWITHROUNDOBJ_H

#include "Point.h"
#include <math.h>
#include "Collision.h"
#include "TriangleCollision.h"

class TriangleCollision;
class Collision;

class RoundCollision{
public:
	RoundCollision();
	RoundCollision(Point loc, float height, float raduis);
	~RoundCollision();

	bool checkPointCollision(Point other);
	bool checkAABBCollision(Collision other);
	bool checkSphereCollision(RoundCollision other);
	bool checkTriCollision(TriangleCollision other);
	Point getLocation();
	void setLocation(Point _loc);
	float getheight();
	void setheight(float height);
	float getraduis();
	void setraduis(float raduis);

private:
	Point loc;
	float height;
	float raduis;
};

#endif