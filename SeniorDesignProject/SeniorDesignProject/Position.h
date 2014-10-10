#pragma once
#include "Direction.h"
#include "Point.h"
#include "LookDirection.h"
class Position
{
public:
	void Init();
	Point* getLocation();
	void setLocation(Point* location);
	LookDirection* getLook();
	Point* getVelocity();
	void setVelocity(Point* speed);
	Point* getAccel();
	void setAccel(Point* accel);
	void teleport(Point* coord);
	void move(Direction direction,float magnitude);
	void lookTo(Direction direction,float magnitude);
	void lookAt(Point* point);
	Position();
	~Position();

private:

protected:
	Point* location;
	LookDirection* look;
	Point* speed;
	Point* accel;
};

