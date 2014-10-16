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

//Begins move in the opposite direction, effectively undoing the velocity that was given by key down.
void Controller::handleKeyUp(char key){
	switch (key){
	case 'w':
		beginMove(Direction::BACK);
		break;
	case 's':
		beginMove(Direction::FRONT);
		break;
	case 'a':
		beginMove(Direction::RIGHT);
		break;
	case 'd':
		beginMove(Direction::LEFT);
		break;


	default:
		break;
	}
}

void Controller::handleKeyDown(char key){
	switch (key){
		
		//MOVE
	case 'w':
		beginMove(Direction::FRONT);
		break;
	case 's':
		beginMove(Direction::BACK);
		break;
	case 'a':
		beginMove(Direction::LEFT);
		break;
	case 'd':
		beginMove(Direction::RIGHT);
		break;

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