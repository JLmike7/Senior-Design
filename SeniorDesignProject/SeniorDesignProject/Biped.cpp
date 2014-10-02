#include "Biped.h"


Biped::Biped()
{

}


Biped::~Biped()
{
}

void Biped::Init()
{
	//stance = Stance->STANDBY;
	//weapons[0];
	teamNumber = 1;
	cameraHeight = 5.0f;
	crawlCameraHeight = 5.0f;
	teamColor = 1;
	fire = false;
}


/*Stance Biped::getStance()
{
	return stance;
}

void Biped::setStance(Stance stance)
{
	Biped::stance = stance;
}*/

/*Weapon Biped::getWeapon(){
	return weapons[10];
}
void Biped::setWeapon(Weapon gunType){

}*/
int Biped::getTeam(){
	return teamNumber;
}
void Biped::setTeam(int team){
	
}
bool Biped::firing(){
	return fire;
}


int Biped::takeHit(int damage)
{
	int hit = damage;
	int placeholder=0; // is placeholder being equal to hit and or damages
	//biped.Health -= damage;
	return placeholder; //biped.Health
}

float Biped::getCameraHeight(){
	return cameraHeight;
}
void Biped::setCameraHeight(float newHeight){
	cameraHeight = newHeight;
}
float Biped::getCrawlCameraHeight(){
	return crawlCameraHeight;
}
void  Biped::setCrawlCameraHeight(float newHeight){
	crawlCameraHeight = newHeight;
}
int Biped::getTeamColor(){
	return teamColor;
}
void Biped::setTeamColor(int newColor){
	teamColor = newColor;
}
