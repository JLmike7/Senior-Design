#pragma once
#include "World.h"
class Settings :
	public World
{
public:
	//Methods
	void Init();
	Settings();
	~Settings();
	bool getFF();
	void setFF(bool FF);
	bool getIsFullScreen();
	void setIsFullScreen(bool isFullScreen);
	int getDetailLevel();
	void setDetailLevel(int level);
	int getTextureLevel();
	void setTextureLevel(int level);
	int getDifficulty();
	void setDifficulty(int level);


private:

protected:
	//Game Settings Fields
	bool			friendlyFire;
	bool			isFullScreen;
	int				detailLevel;
	int				textureLevel;
	int				difficulty;
};

