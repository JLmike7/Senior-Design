#include "Settings.h"


Settings::Settings()
{

}


Settings::~Settings()
{
}

void Settings::Init()
{
	//Initialize Game Settings
	friendlyFire = false;
	difficulty = 2;
	textureLevel = 2;
	detailLevel = true;
	isFullScreen = true;


}

bool Settings::getFF()
{
	return friendlyFire;
}

void Settings::setFF(bool FF)
{
	friendlyFire == FF;
}

bool Settings::getIsFullScreen()
{
	return isFullScreen;
}

void Settings::setIsFullScreen(bool isFullScreen)
{
	
}
