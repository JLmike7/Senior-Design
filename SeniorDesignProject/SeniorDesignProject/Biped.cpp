#include "Biped.h"

Biped::Biped(Settings* _settings){
	Init(_settings);
}

Biped::Biped()
{
	teamNumber = 1;
}


Biped::~Biped()
{

}

void Biped::Init(Settings* _settings)
{
	settings = _settings;
	stance = WALK;
	teamNumber = 1;
}


/*Stance Biped::getStance()
{
	return stance;
}

void Biped::setStance(Stance stance)
{
	Biped::stance = stance;
}*/

/*Weapon Biped::getWeapon(){
	return weapons[10];
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
void Biped::setTeam(int team){
	
}

int Biped::takeHit(int damage)
{
	int hit = damage;
	int placeholder=0; // is placeholder being equal to hit and or damages
	//biped.Health -= damage;
	Stats myStats;
	//myStats.setHealth(myStats.getHealth =- damage);
	return 90; //biped.Health
}

float Biped::getCameraHeight(){
	return cameraHeight;
}
int Biped::takeHit(int damage){
	stats->setHealth(stats->getHealth()-damage);
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
	return death;
}
void Biped::lookAt(Point* point){
	position->lookAt(point);
}
*/