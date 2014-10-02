#pragma once
#include "Point.h"
#include "Triangle.h"

#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_RIGHT 2
#define BOTTOM_LEFT 3

class Quad
{
public:
	Quad();
	Quad(Point *points[4]);
	Quad::Quad(Point* topLeft, Point* topRight, Point* bottomRight, Point* bottomLeft);
	~Quad();

	Triangle** getTriangles();
	Point** getPoints();
	Point* getTopLeft();
	Point* getTopRight();
	Point* getBottomLeft();
	Point* getBottomRight();
	void setPoints(Point *points[4]);
	void setTopLeft(Point *point);
	void setTopRight(Point *point);
	void setBottomLeft(Point *point);
	void setBottomRight(Point *point);
private:
	Point *points[4];
};