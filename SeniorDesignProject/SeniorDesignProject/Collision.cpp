#include "Collision.h"

Collision::Collision(){

}

Collision::Collision(Location _loc, float _height, float _width, float _length){
	loc = _loc;
	height = _height;
	width = _width;
	length = _length;
}

Collision::~Collision(){

}


Location Collision::newLocation(float height){
	Location nloc;
	nloc.setX(loc.getX());
	nloc.setY(loc.getY() + (height / 2));
	nloc.setZ(loc.getZ());
	return loc;
}

bool Collision::checkPointCollision(Location other){
	if (loc.getX() + width >= other.getX() && loc.getX() - width <= other.getX()){
		if (loc.getZ() + length >= other.getZ() && loc.getZ() - length <= other.getZ()){
			if ((loc.getY() + (height) >= other.getY() && loc.getY() - (height) <= other.getY())){
				return true;
			}
		}
	}
	return false;
}

bool Collision::checkAABBCollision(Collision coll){
	if (loc.getX() + width >= coll.getLocation().getX() + coll.getwidth() && loc.getX() - width <= coll.getLocation().getX() - coll.getwidth()){
		if (loc.getZ() + length >= coll.getLocation().getZ() + coll.getlength() && loc.getZ() - length <= coll.getLocation().getZ() - coll.getlength()){
			if ((loc.getY() + height >= coll.getLocation().getY() + coll.getheight() && loc.getY() - height <= coll.getLocation().getY() - coll.getheight())){
				return true;
			}
		}
	}
	return false;
}

bool Collision::checkRoundCollision(RoundCollision other){
	if (loc.getX() + width >= other.getLocation().getX() + other.getraduis() && loc.getX() - width <= other.getLocation().getX() - other.getraduis()){
		if (loc.getZ() + length >= other.getLocation().getZ() + other.getraduis() && loc.getZ() - length <= other.getLocation().getZ() - other.getraduis()){
			if (loc.getY() + height >= other.getLocation().getY() + other.getheight() && loc.getY() - height <= other.getLocation().getY() - other.getheight()){
				return true;
			}
		}
	}
	return false;
}

bool Collision::checkTriCollision(TriangleCollision other){
	if (loc.getX() + width >= other.getLocation().getX() + other.getwidth() && loc.getX() - width <= other.getLocation().getX() - other.getwidth()){
		if (loc.getZ() + length >= other.getLocation().getZ() + (other.getlength() + loc.getY() * cos(other.getangle())) && loc.getZ() - length <= other.getLocation().getZ() - (other.getlength() + loc.getY() * cos(other.getangle()))){
			if (loc.getY() + height >= other.getLocation().getY() + (other.getheight() + loc.getZ() * sin(other.getangle())) && loc.getY() - height <= other.getLocation().getY() - (other.getheight() + loc.getZ() * sin(other.getangle()))){
				return true;
			}
		}
	}
	return false;
}

Location Collision::getLocation(){
	return loc;
}

void Collision::setLocation(Location _loc){
	loc = _loc;
}

float Collision::getheight(){
	return height;
}

void Collision::setheight(float _height){
	height = _height;
}

float Collision::getlength(){
	return length;
}

void Collision::setlength(float _length){
	length = _length;
}

float Collision::getwidth(){
	return width;
}

void Collision::setwidth(float _width){
	width = _width;
}
