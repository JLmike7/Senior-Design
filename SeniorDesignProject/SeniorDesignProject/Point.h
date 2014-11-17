#ifndef POINT_H
#define POINT_H

class Point{
public:
	Point(float x,float y,float z);
	Point();
	~Point();
	float getX();
	float getY();
	float getZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
private:
	float x, y, z;
};

#endif