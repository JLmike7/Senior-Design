#include "TriangleCollision.h"
#include <math.h>
TriangleCollision::TriangleCollision(){

}

TriangleCollision::TriangleCollision(Location _loc, float _height, float _length, float _width){
	loc = _loc;
	height = _height;
	length = _length;
	width = _width;

	angle = length * length + width * width;
	angle = sqrt(angle);
}

TriangleCollision::~TriangleCollision(){

}

bool TriangleCollision::checkPointCollision(Location other) {
	if (loc.getX() + width >= other.getX() && loc.getX() - width <= other.getX()){
		if (loc.getZ() + (length + other.getY() * cos(angle)) >= other.getZ() && loc.getZ() - (length + other.getY() * cos(angle)) <= other.getZ()){
			if ((loc.getY() + (height + other.getZ() * sin(angle)) >= other.getY() && loc.getY() - (height + other.getZ() * sin(angle)) <= other.getY())){
				return true;
			}
		}
	}
	return false;
}

bool TriangleCollision::checkAABBCollision(Collision coll){
	if (loc.getX() + width >= coll.getLocation().getX() + coll.getwidth() && loc.getX() - width <= coll.getLocation().getX() - coll.getwidth()){
		if (loc.getZ() + (length + coll.getLocation().getY() * cos(angle)) >= coll.getLocation().getZ() + coll.getlength() && loc.getZ() - (length + coll.getLocation().getY() * cos(angle))  <= coll.getLocation().getZ() - coll.getlength()){
			if ((loc.getY() + (height + coll.getLocation().getZ() * sin(angle)) >= coll.getLocation().getY() + coll.getheight() && loc.getY() - (height + coll.getLocation().getZ() * sin(angle)) <= coll.getLocation().getY() - coll.getheight())){
				return true;
			}
		}
	}
	return false;
}

bool TriangleCollision::checkRoundCollision(RoundCollision other){
	if (loc.getX() + width >= other.getLocation().getX() + other.getraduis() && loc.getX() - width <= other.getLocation().getX() - other.getraduis()){
		if (loc.getZ() + (length + other.getLocation().getY() * cos(angle)) >= other.getLocation().getZ() + other.getraduis() && loc.getZ() - (length + other.getLocation().getY() * cos(angle)) <= other.getLocation().getZ() - other.getraduis()){
			if (loc.getY() + (height + other.getLocation().getZ() * sin(angle)) >= other.getLocation().getY() + other.getheight() && loc.getY() - (height + other.getLocation().getZ() * sin(angle)) <= other.getLocation().getY() - other.getheight()){
				return true;
			}
		}
	}
	return false;
}

bool TriangleCollision::checkTriCollision(TriangleCollision other){
	if (loc.getX() + width >= other.getLocation().getX() + other.getwidth() && loc.getX() - width <= other.getLocation().getX() - other.getwidth()){
		if (loc.getZ() + (length + other.getLocation().getY() * cos(angle)) >= other.getLocation().getZ() + (length + loc.getY() * cos(angle)) && loc.getZ() - (length + other.getLocation().getY() * cos(angle)) <= other.getLocation().getZ() - (length + loc.getY() * cos(angle))){
			if (loc.getY() + (height + other.getLocation().getZ() * sin(angle)) >= other.getLocation().getY() + (height + loc.getZ() * sin(angle)) && loc.getY() - (height + other.getLocation().getZ() * sin(angle)) <= other.getLocation().getY() - (height + loc.getZ() * sin(angle))){
				return true;
			}
		}
	}
	return false;
}

float TriangleCollision::getangle(){
	return angle;
}

void TriangleCollision::setangle(float _angle){
	angle = _angle;
}

float TriangleCollision::getheight(){
	return height;
}

void TriangleCollision::setheight(float _height){
	height = _height;
}

float TriangleCollision::getlength(){
	return length;
}

void TriangleCollision::setlength(float _length){
	length = _length;
}

float TriangleCollision::getwidth(){
	return width;
}

void TriangleCollision::setwidth(float _width){
	width = _width;
}

Location TriangleCollision::getLocation(){
	return loc;
}

void TriangleCollision::setLocation(Location _loc){
	loc = _loc;
}
