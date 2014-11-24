#include "Friendly.h"

Friendly::Friendly(Point pos, Point lookat, Point up, int health, int kills, int deaths) : Position(pos, lookat, up), Stats(health, kills, deaths){

}

Friendly::~Friendly(){

}