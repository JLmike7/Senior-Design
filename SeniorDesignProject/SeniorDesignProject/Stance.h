#pragma once
#include "Biped.h"
class Stance :
	public Biped
{
public:
	Stance Stationary();
	Stance Running();
	Stance Walking();
	Stance Crawling();


	Stance();
	~Stance();

private:

protected:

};

