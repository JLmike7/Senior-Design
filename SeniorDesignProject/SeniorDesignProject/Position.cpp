#include "Position.h"

#define RAD2DEG (180.0f/3.14159f)
#define DEG2RAD (1)
//#define DEG2RAD (3.14159f/180.0f)


Position::Position(Point poss, Point look, Point Up){
	pos = poss;
	lookat = look;
	up = Up;
}


Position::~Position(){
}

Point Position::getpos(){
	return pos;
}

Point Position::getlook(){
	return lookat;
}

Point Position::getup(){
	return up;
}

void Position::setpos(Point poss){
	pos = poss;
}

void Position::setlook(Point look){
	lookat = look;
}

void Position::setup(Point Up){
	up = Up;
}

void Position::updatePos(Point poss, Point look, Point Up){
	pos = poss;
	lookat = look;
	up = Up;
}