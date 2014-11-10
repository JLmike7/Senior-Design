#ifndef COLLISION_H
#define COLLISION_H

#include "Point.h"
#include <math.h>
#include "Collisionwithroundobj.h"
#include "TriangleCollision.h"

class TriangleCollision;
class RoundCollision;

class Collision{
public:
	Collision();
	Collision(Point _loc, float _height, float _length, float _width);
	~Collision();

	bool checkPointCollision(Point other);
	bool checkAABBCollision(Collision other);
	bool checkRoundCollision(RoundCollision other);
	bool checkTriCollision(TriangleCollision other);
	Point newLocation(float height);
	Point getLocation();
	void setLocation(Point _loc);
	float getheight();
	void setheight(float _height);
	float getlength();
	void setlength(float _length);
	float getwidth();
	void setwidth(float _width);
private:
	Point loc;
	float height;
	float length;
	float width;
};

#endif