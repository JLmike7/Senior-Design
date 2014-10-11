#include "Controller.h"
#include "Direction.h"


Controller::Controller()
{
}


Controller::~Controller()
{
}

void Controller::beginMove(Direction direction){
	biped->beginMove(direction);
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
void Controller::nextWeapon(){
	biped->nextWeapon();
}
void Controller::prevWeapon(){
	biped->prevWeapon();
}
void Controller::halt(){
	biped->halt();
}
void Controller::handleKeyPress(char key){
	switch (key){
	case 'w':
		if (!movingFront){
			movingFront = true;
			beginMove(Direction::FRONT);
		}
		break;
	case 's':
		if (!movingBack){
			movingBack = true;
			beginMove(Direction::BACK);
		}
		break;
	case 'a':
		if (!movingBack){
			movingLeft = true;
			beginMove(Direction::LEFT);
		}
		break;
	case 'd':
		if (!movingRight){
			movingRight = true;
			beginMove(Direction::RIGHT);
		}
		break;
	case ' ':
		jump();
		break;
	case '4':
		look(Direction::LEFT);
		break;
	case '6':
		look(Direction::RIGHT);
		break;
	case '8':
		look(Direction::UP);
		break;
	case '2':
		look(Direction::DOWN);
		break;
	case '0':
		fire();
		break;
	case 'q':
		prevWeapon();
		break;
	case 'e':
		nextWeapon();
		break;
	default:
		halt();
	}
}