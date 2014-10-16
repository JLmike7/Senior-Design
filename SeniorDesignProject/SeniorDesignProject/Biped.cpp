#include "Biped.h"
#include "Stats.h"
#include "Settings.h"

Biped::Biped(Settings* _settings,Box* box){
	Init(_settings,box);
}

Biped::Biped()
{
}

Biped::~Biped()
{
}

void Biped::Init(Settings* _settings,Box* box)
{
	settings = _settings;
	stance = WALK;
	teamNumber = 1;
	hitbox = box;
}
Stance Biped::getStance()
{
	return stance;
}
void Biped::setStance(Stance _stance)
{
	stance = _stance;
}
//You can get position, but there is no set Position.  Use getPosition->teleport() to set position.
Position* Biped::getPosition()
{
	return position;
}
void Biped::beginMove(Direction direction){
	if (stance == Stance::WALK){
		position->beginMove(direction, stats->getMaxWalk());
	}
	else if (stance == Stance::CRAWL){
		position->beginMove(direction, stats->getMaxCrawl());
	}
	else if (stance == Stance::RUN){
		position->beginMove(direction, stats->getMaxRun());
	}
}
Box* Biped::getHitbox(){
	return hitbox;
}
void Biped::setHitbox(Box* box){
	hitbox = box;
}
Weapon* Biped::getWeapon(){
	return & weapons->front();
}
void Biped::addWeapon(Weapon *newWeapon){
	weapons->push_front(*newWeapon);
}
int Biped::getTeam(){
	return teamNumber;
}
void Biped::nextWeapon(){
	weapons->push_back(weapons->front());
	weapons->pop_front();
}
void Biped::prevWeapon(){
	weapons->push_front(weapons->back());
	weapons->pop_back();
}
void Biped::setTeam(int _team){
	teamNumber = _team;
}
int Biped::takeHit(int damage){
	stats->setHealth(stats->getHealth()-damage);
}
void Biped::jump(){
	if (position->isOnGround()){
		position->beginMove(Direction::UP, stats->getMaxJumpSpeed());
	}
}
void Biped::fire(){
	//TODO: implement
}
bool Biped::isDead(){
	return stats->isDead();
}
void Biped::lookTo(Direction direction){
	position->lookTo(direction,(float)settings->getLookSensitivity());
}
void Biped::lookAt(Point* point){
	position->lookAt(point);
}
