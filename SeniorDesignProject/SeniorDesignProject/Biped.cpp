#include "Biped.h"
#include "Stats.h"
#include "Settings.h"

Biped::Biped(Point pos, Point lookat, Point up, int health, int kills, int deaths) : Position(pos, lookat, up), Stats(health, kills, deaths) {
	//box = coll;
	//stance = _stance;
}

Biped::~Biped()
{

}

Stance Biped::getStance()
{
	return stance;
}
void Biped::setStance(Stance _stance)
{
	stance = _stance;
}

Weapon* Biped::getWeapon(){
	return & weapons->front();
}
void Biped::addWeapon(Weapon *newWeapon){
	weapons->push_front(*newWeapon);
}
void Biped::nextWeapon(){
	weapons->push_back(weapons->front());
	weapons->pop_front();
}
void Biped::prevWeapon(){
	weapons->push_front(weapons->back());
	weapons->pop_back();
}

void Biped::fire(){
	//TODO: implement when the weapon is applied
}