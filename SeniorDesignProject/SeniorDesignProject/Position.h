#pragma once
#include "Point.h"
#include "LookDirection.h"
class Position
{
public:
	void Init();
	Point* getLocation();
	LookDirection* getLook();
	Point* getVelocity();
	void setVelocity(Point* speed);
	void addVelocity(Point* speed);
	Point* getAccel();
	void setAccel(Point* accel);
	void addAccel(Point* accel);
	void teleport(Point* coord);
	void lookAt(Point* point);
	bool isOnGround();
	void halt();
	void applyTickMovement();
	Position();
	~Position();

private:

protected:
	Point* location;
	LookDirection* look;
	Point* velocity;
	Point* accel;
};

