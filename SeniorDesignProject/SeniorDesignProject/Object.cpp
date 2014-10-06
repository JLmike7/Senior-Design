#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}

void Object::Init()
{
	isDead = false;
}

bool Object::getDeath()
{
	return isDead;
}
void Object::setDeath(bool isDead)
{
	Object::isDead = isDead;
}