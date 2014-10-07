#pragma once
class Settings
{
public:
	//Methods
	void Init();
	bool getFF();
	void setFF(bool FF);
	bool getIsFullScreen();
	void setIsFullScreen(bool FS);
	int getDetailLevel();
	void setDetailLevel(int level);
	int getTextureLevel();
	void setTextureLevel(int level);
	int getDifficulty();
	void setDifficulty(int level);
	int getMovementSensitivity();
	void setMovementSensitivity(int level);
	int getLookSensitivity();
	void setLookSensitivity(int level);
	Settings();
	~Settings();

private:

protected:
	//Game Settings Fields
	bool			friendlyFire;
	bool			isFullScreen;
	int				detailLevel;
	int				textureLevel;
	int				difficulty;
	int				movementSensitivity;
	int				lookSensitivity;
};

