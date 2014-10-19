#pragma once
#include "Quad.h"
#include "Point.h"
#include "Triangle.h"
#include "Direction.h"
#include <stdexcept>

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
	Box(Point* center, float width, float height, float depth);
	~Box();

	void setFromWHD(Point* center,float width, float height, float depth);

	Triangle** getInwardTriangles();
	Triangle** getOutwardTriangles();
	Quad** getInwardQuads();
	Quad** getOutwardQuads();

	//get the quad facing outward
	Quad* getOutwardFace(Direction d);
	Quad* getOutwardTop();
	Quad* getOutwardBottom();
	Quad* getOutwardLeft();
	Quad* getOutwardRight();
	Quad* getOutwardFront();
	Quad* getOutwardBack();

	//get the quad facing inward
	Quad* getInwardFace(Direction d);
	Quad* getInwardTop();
	Quad* getInwardBottom();
	Quad* getInwardLeft();
	Quad* getInwardRight();
	Quad* getInwardFront();
	Quad* getInwardBack();


protected:
	void rectanglesToTriangles(Quad** from, Triangle** to, int size);
	void copyTriangles(Triangle** from, Triangle** to, int size);
	Point *points[8];
};