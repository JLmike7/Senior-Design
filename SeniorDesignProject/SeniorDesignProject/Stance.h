#pragma once
#include "Person.h"
class Stance :
	public Person
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

