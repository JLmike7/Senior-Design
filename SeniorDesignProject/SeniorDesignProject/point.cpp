#include "Point.h"
#include <math.h>


Point::Point(){

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
void Point::addY(float _z){
	z += _z;
}

void Point::move(Point* other){
	move(other->getCoords);
}
void Point::move(float coords[3]){
	addX(coords[0]);
	addY(coords[1]);
	addY(coords[2]);
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