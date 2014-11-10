#include "Stats.h"


Stats::Stats()
{
	Init();
}


Stats::~Stats()
{
}

void Stats::Init(){
	maxHealth = 100;
	health = 100;
	strength = 50;
	lives = 3;
	//mode;
	//AMode;
	maxCrawlSpeed = 10.0f;
	maxWalkSpeed = 20.0f;
	maxRunSpeed = 50.0f;
	maxSpeed = 200.0f;
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

bool Stats::isDead(){
	return (health < 1);
}
