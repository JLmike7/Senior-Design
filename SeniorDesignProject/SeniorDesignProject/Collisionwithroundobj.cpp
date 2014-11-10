#include "Collisionwithroundobj.h"

RoundCollision::RoundCollision(){

}

RoundCollision::RoundCollision(Location _loc, float _height, float _raduis){
	loc = _loc;
	height = _height;
	raduis = _raduis;
}

RoundCollision::~RoundCollision(){

}

bool RoundCollision::checkAABBCollision(Collision other){
	if (loc.getX() + raduis >= other.getLocation().getX() + other.getwidth() && loc.getX() - raduis <= other.getLocation().getX() - other.getwidth()){
		if (loc.getZ() + raduis >= other.getLocation().getZ() + other.getlength() && loc.getZ() - raduis <= other.getLocation().getZ() - other.getlength()){
			if (loc.getY() + raduis >= other.getLocation().getY() + other.getheight() && loc.getY() - raduis <= other.getLocation().getY() - other.getheight()){
				return true;
			}
		}
	}
	return false;
}

bool RoundCollision::checkPointCollision(Location other){
	if (loc.getX() + raduis >= other.getX() && loc.getX() - raduis <= other.getX()){
		if (loc.getZ() + raduis >= other.getZ() && loc.getZ() - raduis <= other.getZ()){
			if (loc.getY() + raduis >= other.getY() && loc.getY() - raduis <= other.getY()){
				return true;
			}
		}
	}
	return false;
}

bool RoundCollision::checkSphereCollision(RoundCollision other){
	if (loc.getX() + raduis >= other.getLocation().getX() + other.getraduis() && loc.getX() - raduis <= other.getLocation().getX() - other.getraduis()){
		if (loc.getZ() + raduis >= other.getLocation().getZ() + other.getraduis() && loc.getZ() - raduis <= other.getLocation().getZ() - other.getraduis()){
			if (loc.getY() + raduis >= other.getLocation().getY() + other.getheight() && loc.getY() - raduis <= other.getLocation().getY() - other.getheight()){
				return true;
			}
		}
	}
	return false;
}

bool RoundCollision::checkTriCollision(TriangleCollision other){
	if (loc.getX() + raduis >= other.getLocation().getX() + other.getwidth() && loc.getX() - raduis <= other.getLocation().getX() - other.getwidth()){
		if (loc.getZ() + raduis >= other.getLocation().getZ() + (other.getlength() + loc.getY() * cos(other.getangle())) && loc.getZ() - raduis <= other.getLocation().getZ() - (other.getlength() + loc.getY() * cos(other.getangle()))){
			if (loc.getY() + height >= other.getLocation().getY() + (other.getheight() + loc.getZ() * sin(other.getangle())) && loc.getY() - height <= other.getLocation().getY() - (other.getheight() + loc.getZ() * sin(other.getangle()))){
				return true;
			}
		}
	}
	return false;
}

Location RoundCollision::getLocation(){
	return loc;
}

void RoundCollision::setLocation(Location _loc){
	loc = _loc;
}

float RoundCollision::getheight(){
	return height;
}

void RoundCollision::setheight(float _height){
	height = _height;
}

float RoundCollision::getraduis(){
	return raduis;
}

void RoundCollision::setraduis(float _raduis){
	raduis = _raduis;
}