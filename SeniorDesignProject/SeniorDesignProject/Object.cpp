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

void Object::setGravityEnabled(bool gravity){
	gravityEnabled = gravity;
}

bool Object::isGravityEnabled(){
	return gravityEnabled;
}

void Object::Init(Box hitbox)
{
	gravityEnabled = false;
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