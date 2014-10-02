#pragma once
class Point
{
public:
	//Creates a point at the origin (0,0,0) by default.
	Point();
	Point(float x,float y,float z);
	Point(float coords[3]);
	~Point();
	float getX();
	float getY();
	float getZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	float distanceTo(Point* other);
private:
	float x, y, z;
};