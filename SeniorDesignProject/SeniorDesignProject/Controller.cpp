#include "Controller.h"
#include "Direction.h"


Controller::Controller()
{
}


Controller::~Controller()
{
}

void Controller::move(Direction direction){
	biped->move(direction);
}
void Controller::look(Direction direction){
	biped->lookTo(direction);
}
void Controller::fire(){
	biped->fire();
}
void Controller::jump(){
	biped->jump();
}
