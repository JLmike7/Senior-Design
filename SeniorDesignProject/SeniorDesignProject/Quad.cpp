#include "Quad.h"

//By default, quad is the unit square on the xy axis, centered through to the z axis.
Quad::Quad(){
	points[TOP_LEFT]= new Point(-.5,.5,0);
	points[TOP_RIGHT] = new Point(.5, .5, 0);
	points[BOTTOM_RIGHT] = new Point(.5, -.5, 0);
	points[BOTTOM_LEFT] = new Point(-.5, -.5, 0);
}
Quad::Quad(Point *_points[4]){
	setPoints(_points);
}
Quad::Quad(Point* topLeft, Point* topRight, Point* bottomRight, Point* bottomLeft){
	points[TOP_LEFT] = topLeft;
	points[TOP_RIGHT] = topRight;
	points[BOTTOM_RIGHT] = bottomRight;
	points[BOTTOM_LEFT] = bottomRight;
}
Quad::~Quad()
{
}

Triangle** Quad::getTriangles(){
	Triangle* triangles[2];
	triangles[0] = new Triangle(points[0],points[2],points[1]);
	triangles[1] = new Triangle(points[0],points[4],points[3]);
	return triangles;
}
Point** Quad::getPoints(){
	return points;
}
Point* Quad::getTopLeft(){
	return points[TOP_LEFT];
}
Point* Quad::getTopRight(){
	return points[TOP_RIGHT];
}
Point* Quad::getBottomLeft(){
	return points[BOTTOM_LEFT];
}
Point* Quad::getBottomRight(){
	return points[BOTTOM_RIGHT];
}
void Quad::setPoints(Point *_points[4]){
	points[0] = _points[0];
	points[1] = _points[1];
	points[2] = _points[2];
	points[3] = _points[3];
}
void Quad::setTopLeft(Point *point){
	points[TOP_LEFT]= point;
}
void Quad::setTopRight(Point *point){
	points[TOP_RIGHT]= point;
}
void Quad::setBottomLeft(Point *point){
	points[BOTTOM_LEFT]= point;
}
void Quad::setBottomRight(Point *point){
	points[BOTTOM_RIGHT] = point;
}