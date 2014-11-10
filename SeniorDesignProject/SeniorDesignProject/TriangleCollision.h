#ifndef TRIANGLECOLLISION_H
#define TRIANGLECOLLISION_H

#include "Point.h"
#include <math.h>
#include "Collision.h"
#include "Collisionwithroundobj.h"

class Collision;
class RoundCollision;

class TriangleCollision{
public:
	TriangleCollision();
	TriangleCollision(Point _loc, float _height, float _length, float _width);
	~TriangleCollision();

	bool checkPointCollision(Point other);
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
	Point getLocation();
	void setLocation(Point _loc);

private:
	Point loc;
	float height;
	float length;
	float width;
	float angle;
};

#endif