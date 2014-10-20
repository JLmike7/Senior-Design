#include "Point.h"
#include <math.h>


Point::Point(){
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

//Creates a point at the origin (0,0,0) by default.
Point::Point(float _x,float _y,float _z){
	x = _x;
	y = _y;
	z = _z;
}
Point::Point(float coords[3]){
	x = coords[0];
	y = coords[1];
	z = coords[2];
}

Point::~Point(){

}

void Point::setX(float _x){
	x=_x;
}
void Point::setY(float _y){
	y = _y;
}
void Point::setZ(float _z){
	z = _z;
}

void Point::addX(float _x){
	x += _x;
}
void Point::addY(float _y){
	y += _y;
}
void Point::addZ(float _z){
	z += _z;
}

void Point::move(Point* other){
	addX(other->getX());
	addY(other->getY());
	addZ(other->getZ());
}

float Point::getX(){
	return x;
}
float Point::getY(){
	return y;
}
float Point::getZ(){
	return z;
}

float* Point::getCoords(){
	float coords[3] = { x, y, z };
	return coords;
}

float Point::distanceTo(Point* other){
	return sqrt(
		pow(other->getX() - getX(), 2) + 
		pow(other->getY() - getY(), 2) + 
		pow(other->getZ() - getZ(),2) );
}

Point* Point::diff(Point* other){
	Point* diff = new Point();
	diff->setX(x - other->getX());
	diff->setY(y - other->getY());
	diff->setZ(z - other->getZ());
	return diff;
}