#include "Enemy.h"

Enemy::Enemy(Point pos, Point lookat, Point up, int health, int kills, int deaths) : Stats(health, kills, deaths), Position(pos, lookat, up){

}

Enemy::~Enemy(){

}
