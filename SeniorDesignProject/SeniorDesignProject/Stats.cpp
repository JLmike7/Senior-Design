#include "Stats.h"


Stats::Stats()
{
	maxHealth = 100;
	health = 100;
	strength = 50;
	lives = 3;
	//hitBox;
	//mode;
	//AMode;
	maxCrawlSpeed = 25.0f;
	maxWalkSpeed = 60.0f;
	maxRunSpeed = 100.0f;
	maxSpeed = 200.0f;
	inUse = false;
}


Stats::~Stats()
{
}

void Stats::Init(){
	
}

//Getters/Settings for Stats.
int Stats::getMaxHealth(){
	return maxHealth;
}

void Stats::setMaxHealth(int newHealth){
	maxHealth = newHealth;
}

int Stats::getHealth(){
	return health;
}

void Stats::setHealth(int currentHealth){
	health = currentHealth;
}

int Stats::getStrength(){
	return strength;
}

void Stats::setStrength(int newStrength){
	strength = newStrength;
}

int Stats::getLives(){
	return lives;
}

void Stats::setLives(int currentLives){
	lives = currentLives;
}

float Stats::getMaxCrawl(){
	return maxCrawlSpeed;
}

void Stats::setMaxCrawl(float newMaxCrawl){
	maxCrawlSpeed = newMaxCrawl;
}

float Stats::getMaxWalk(){
	return maxWalkSpeed;
}

void Stats::setMaxWalk(float newMaxWalk){
	maxWalkSpeed = newMaxWalk;
}

float Stats::getMaxRun(){
	return maxRunSpeed;
}

void Stats::setMaxRun(float newMaxRun){
	maxRunSpeed = newMaxRun;
}

float Stats::getMaxSpeed(){
	return maxSpeed;
}
void Stats::setMaxSpeed(float newMaxSpeed){
	maxSpeed = newMaxSpeed;
}
float Stats::getMaxJumpSpeed(){
	return maxJumpSpeed;
}
void Stats::setMaxJumpSpeed(float newMaxJumpSpeed){
	maxSpeed = newMaxJumpSpeed;
}

bool Stats::getInUse(){
	return inUse;
}

void Stats::setInUse(bool newStatus){
	inUse = newStatus;
}


