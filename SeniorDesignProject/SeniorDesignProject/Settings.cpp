#include "Settings.h"


Settings::Settings()
{
	friendlyFire = false;
	difficulty = 2;
	textureLevel = 2;
	detailLevel = 2;
	isFullScreen = true;
	movementSensitivity = 5;
	lookSensitivity = 5;
}


Settings::~Settings()
{
}

void Settings::Init()
{
	//Initialize Game Settings
	

}

//Get Friendly Fire Status
bool Settings::getFF()
{
	return friendlyFire;
}

//Set Friendly Fire Status
void Settings::setFF(bool FF)
{
	friendlyFire = FF;
}

//Get Full Screen Status
bool Settings::getIsFullScreen()
{
	return isFullScreen;
}

//Set Full Screen Status
void Settings::setIsFullScreen(bool FS)
{
	isFullScreen = FS;
}

//Get Difficulty
int Settings::getDifficulty()
{
	return difficulty;
}

//Set Difficulty
void Settings::setDifficulty(int level)
{
	difficulty = level;
}

//Get Textures
int Settings::getTextureLevel()
{
	return textureLevel;
}

//Set Textures
void Settings::setTextureLevel(int level)
{
	textureLevel = level;
}

//Get Detail
int Settings::getDetailLevel()
{
	return detailLevel;
}

//Set Detail
void Settings::setDetailLevel(int level)
{
	detailLevel = level;
}

//Get movement sensitivity
int Settings::getMovementSensitivity(){
	return movementSensitivity;
}
//Set movement sensitivity
void Settings::setMovementSensitivity(int level){
	movementSensitivity = level;
}

//Get look sensitivity
int Settings::getLookSensitivity(){
	return lookSensitivity;
}
//Set look sensitivity
void Settings::setLookSensitivity(int level){
	lookSensitivity = level;
}

