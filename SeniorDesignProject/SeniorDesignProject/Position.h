#pragma once
#include "Direction.h"
#include "Coord.h"
class Position
{
public:
	void Init();
	Coord getLocation();
	void setLocation(Coord location);
	Coord getLook();
	void setLook(Coord look);
	Coord getSpeed();
	void setSpeed(Coord speed);
	Coord getAccel();
	void setAccel(Coord accel);
	void teleport(Coord coord);
	int move(Direction direction);
	int lookAt(Direction direction);
	bool jump();
	Position();
	~Position();

private:

protected:
	Coord location;
	Coord look;
	Coord speed;
	Coord accel;
};

