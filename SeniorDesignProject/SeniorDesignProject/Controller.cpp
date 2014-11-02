#include "Controller.h"
#include "Direction.h"


Controller::Controller()
{
}


Controller::~Controller()
{
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

void Controller::handleKey(char key){
	if (key == 'w'){
		biped->walk(Direction::FRONT, true);
	}
	else
		biped->walk(Direction::FRONT, false);

	if (key == 's'){
		biped->walk(Direction::BACK, true);
	}
	else
		biped->walk(Direction::BACK, false);

	if (key == 'a'){
		biped->walk(Direction::LEFT, true);
	}
	else
		biped->walk(Direction::LEFT, false);

	if (key == 'd'){
		biped->walk(Direction::RIGHT, true);
	}
	else
		biped->walk(Direction::RIGHT, false);

	switch (key){
		//LOOK
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

		//OTHER
	case '0':
		fire();
		break;
	case ' ':
		jump();
		break;
	case 'q':
		prevWeapon();
		break;
	case 'e':
		nextWeapon();
		break;


	default:
		break;
	}
}