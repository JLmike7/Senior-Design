#include "Biped.h"
#include "Stats.h"
#include "Settings.h"

Biped::Biped(Settings* _settings)
{
	Init(_settings);
}


Biped::~Biped()
{
}

void Biped::Init(Settings* _settings)
{
	settings = _settings;
	stance = WALK;
	teamNumber = 1;
	cameraHeight = 5.0f;
	crawlCameraHeight = 5.0f;
	teamColor = 1;
}
Biped::Stance Biped::getStance()
{
	return stance;
}
void Biped::setStance(Stance _stance)
{
	stance = _stance;
}
Position* Biped::getPosition()
{
	return position;
}
void Biped::setPosition(Position *_position)
{
	position = position;
}
void Biped::move(Direction direction){
	if (stance == Stance::WALK){
		position->move(direction, stats->getMaxWalk());
	}
	else if (stance == Stance::CRAWL){
		position->move(direction, stats->getMaxCrawl());
	}
	else if (stance == Stance::RUN){
		position->move(direction, stats->getMaxRun());
	}
}
Weapon* Biped::getWeapon(){
	return & weapons->front();
}
void Biped::pushWeapon(Weapon *newWeapon){
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
		position->addVelocity(new Point(0.0, stats->getMaxJumpSpeed(), 0.0));
	}
}
void Biped::fire(){
	//TODO: implement
}

float Biped::getCameraHeight(){
	return cameraHeight;
}
void Biped::setCameraHeight(float newHeight){
	cameraHeight = newHeight;
}
float Biped::getCrawlCameraHeight(){
	return crawlCameraHeight;
}
void  Biped::setCrawlCameraHeight(float newHeight){
	crawlCameraHeight = newHeight;
}
int Biped::getTeamColor(){
	return teamColor;
}
void Biped::setTeamColor(int newColor){
	teamColor = newColor;
}
bool Biped::getDeath(){
	return dead;
}
void Biped::setDeath(bool isDead){
	dead = isDead;
}
void Biped::lookTo(Direction direction){
	position->lookTo(direction,(float)settings->getLookSensitivity());
}
void Biped::lookAt(Point* point){
	position->lookAt(point);
}
