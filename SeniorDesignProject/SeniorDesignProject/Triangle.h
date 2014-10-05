#pragma once
#include "Point.h"

class Triangle
{
public:
	Triangle();
	Triangle(Point* point1, Point* point2, Point* point3);
	Triangle(Point* points[3]);
	~Triangle();

	void setPoint(int index, Point* value);
	void setPoints(Point* points[3]);
	Point* Triangle::getPoint(int index);
	Point** Triangle::getPoints();
private:
	Point* points[3];
};