#include "Biped.h"
#include "Stats.h"
#include "Settings.h"

Biped::Biped(Settings* _settings){
	Init(_settings);
}

Biped::Biped()
{
}

Biped::~Biped()
{

}

void Biped::Init(Settings* _settings)
{
	position = new Position();
	settings = _settings;
	stance = WALK;
	teamNumber = -1;
	hitbox = new Box(position->getLocation(),HIT_BOX_WIDTH,HIT_BOX_HEIGHT,HIT_BOX_DEPTH);
}
Stance Biped::getStance()
{
	return stance;
}
void Biped::setStance(Stance _stance)
{
	stance = _stance;
}
//You can get position, but there is no set Position.  Use getPosition->teleport() to set a new location.
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
void Biped::makeWalk(Direction direction){
	if (walkingStatus->isWalking(direction)){
		//Do nothing, you're already walking
	}
	else{
		walkingStatus->setTrue(direction);
		beginMove(direction);
	}
}
void Biped::makeNotWalk(Direction direction){
	if (walkingStatus->isWalking(direction)){
		walkingStatus->setFalse(direction);
		if (direction == Direction::FRONT){
			beginMove(Direction::BACK);
		}
		if (direction == Direction::BACK){
			beginMove(Direction::FRONT);
		}
		if (direction == Direction::LEFT){
			beginMove(Direction::RIGHT);
		}
		if (direction == Direction::RIGHT){
			beginMove(Direction::LEFT);
		}
	}
	else{
		//Do nothing, you're already stopped
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
void Biped::takeHit(int damage){
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
void Biped::lookAt(Point* point,bool tracking){
	position->lookAt(point,tracking);
}
