#include "Object.h"


Object::Object(Box hitbox)
{
	Init(hitbox);
}

Object::Object()
{
}


Object::~Object()
{
}

void Object::Init(Box hitbox)
{
	isDead = false;
	hitbox = hitbox;
}

bool Object::getDeath()
{
	return isDead;
}
void Object::setDeath(bool isDead)
{
	Object::isDead = isDead;
}

Position* Object::getPosition()
{
	return position;
}
void Object::setPosition(Position *_position)
{
	position = position;
}