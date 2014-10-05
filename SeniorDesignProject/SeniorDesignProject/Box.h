#pragma once
#include "Quad.h"
#include "Point.h"
#include "Triangle.h"

#define FRONT_TOP_LEFT 0
#define FRONT_TOP_RIGHT 1
#define BACK_TOP_RIGHT 2
#define BACK_TOP_LEFT 3
#define FRONT_BOTTOM_LEFT 4
#define FRONT_BOTTOM_RIGHT 5
#define BACK_BOTTOM_RIGHT 6
#define BACK_BOTTOM_LEFT 7

#define TOP_FACE 0
#define BOTTOM_FACE 1
#define LEFT_FACE 2
#define RIGHT_FACE 3
#define FRONT_FACE 4
#define BACK_FACE 5

class Box
{
public:
	Box();
	Box(Point* _points[8]);
	~Box();

	Triangle** getInwardTriangles();
	Triangle** getOutwardTriangles();
	Quad** getInwardRectangles();
	Quad** getOutwardRectangles();

	Quad* getOutwardTop();
	Quad* getOutwardBottom();
	Quad* getOutwardLeft();
	Quad* getOutwardRight();
	Quad* getOutwardFront();
	Quad* getOutwardBack();

	Quad* getInwardTop();
	Quad* getInwardBottom();
	Quad* getInwardLeft();
	Quad* getInwardRight();
	Quad* getInwardFront();
	Quad* getInwardBack();


private:
	Point *points[8];
};