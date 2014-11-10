#ifndef TRIANGLECOLLISION_H
#define TRIANGLECOLLISION_H

#include "Location.h"
#include <math.h>
#include "Collision.h"
#include "Collisionwithroundobj.h"

class Collision;
class RoundCollision;

class TriangleCollision{
public:
	TriangleCollision();
	TriangleCollision(Location _loc, float _height, float _length, float _width);
	~TriangleCollision();

	bool checkPointCollision(Location other);
	bool checkAABBCollision(Collision other);
	bool checkRoundCollision(RoundCollision other);
	bool checkTriCollision(TriangleCollision other);
	float getheight();
	void setheight(float _height);
	float getlength();
	void setlength(float _length);
	float getwidth();
	void setwidth(float _width);
	float getangle();
	void setangle(float _angle);
	Location getLocation();
	void setLocation(Location _loc);

private:
	Location loc;
	float height;
	float length;
	float width;
	float angle;
};

#endif