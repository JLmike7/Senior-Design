#include "Stats.h"

Stats::Stats(int _health, int _kills, int _deaths){
	health = _health;
	kills = _kills;
	deaths = _deaths;
}

Stats::~Stats()
{
}

int Stats::getHealth(){
	return health;
}

void Stats::setHealth(int currentHealth){
	health = currentHealth;
}

int Stats::getkills(){
	return kills;
}

void Stats::setkills(int _kills){
	kills = _kills;
}

int Stats::getdeaths(){
	return deaths;
}

void Stats::setdeaths(int _deaths){
	deaths = _deaths;
}

void Stats::regenerate(){
	if (health < MAXHEALTH){
		health++;
	}else{
	}
}

bool Stats::isDead(){
	if (health <= 0){
		return true;
	}else {
		return false;
	}
}

//void Stats::Init(){
	//maxHealth = 100;  // regeneration?
	//health = 100;
	//strength = 50;
	//lives = 3;
	// why in stats 
	//maxCrawlSpeed = 10.0f;
	//maxWalkSpeed = 20.0f;
	//maxRunSpeed = 50.0f;
	//maxSpeed = 200.0f;
//}

//Getters/Settings for Stats.
//int Stats::getMaxHealth(){
	//return maxHealth;
//}

//void Stats::setMaxHealth(int newHealth){
	//maxHealth = newHealth;
//}

//int Stats::getStrength(){
//	return strength;
//}

//void Stats::setStrength(int newStrength){
//	strength = newStrength;
//}

//float Stats::getMaxCrawl(){
//	return maxCrawlSpeed;
//}
/*
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
*/

