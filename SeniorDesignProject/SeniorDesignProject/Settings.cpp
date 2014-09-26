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

//Get Friendly Fire Status
bool Settings::getFF()
{
	return friendlyFire;
}

//Set Friendly Fire Status
void Settings::setFF(bool FF)
{
	friendlyFire == FF;
}

//Get Full Screen Status
bool Settings::getIsFullScreen()
{
	return isFullScreen;
}

//Set Full Screen Status
void Settings::setIsFullScreen(bool FS)
{
	isFullScreen == FS;
}

//Get Difficulty
int Settings::getDifficulty()
{
	return difficulty;
}

//Set Difficulty
void Settings::setDifficulty(int level)
{
	difficulty == level;
}

//Get Textures
int Settings::getTextureLevel()
{
	return textureLevel;
}

//Set Textures
void Settings::setTextureLevel(int level)
{
	textureLevel == level;
}

//Get Detail
int Settings::getDetailLevel()
{
	return detailLevel;
}

//Set Detail
void Settings::setDetailLevel(int level)
{
	detailLevel == level;
}
