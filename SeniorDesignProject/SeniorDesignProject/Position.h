#ifndef POSITION_H
#define POSITION_H

#include "Point.h"

class Position {
public:
	Position(Point poss, Point look, Point Up);
	~Position();

	Point getpos();
	Point getlook();
	Point getup();
	void setpos(Point poss);
	void setlook(Point look);
	void setup(Point Up);

	void updatePos(Point poss, Point look, Point Up);
	
private:
	Point pos;
	Point lookat;
	Point up;
};

#endif


