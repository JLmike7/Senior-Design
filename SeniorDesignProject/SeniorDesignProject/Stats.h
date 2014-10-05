#pragma once
class Stats
{
public:
	void Init();
	int getMaxHealth();
	void setMaxHealth(int newHealth);
	int getHealth();
	void setHealth(int currentHealth);
	int getStrength();
	void setStrength(int newStrength);
	int getLives();
	void setLives(int currentLives);
	float getMaxCrawl();
	void setMaxCrawl(float newMaxCrawl);
	float getMaxWalk();
	void setMaxWalk(float newMaxWalk);
	float getMaxRun();
	void setMaxRun(float newMaxRun);
	float getMaxSpeed();
	void setMaxSpeed(float newMaxSpeed);
	bool getInUse();
	void setInUse(bool newStatus);
	Stats();
	~Stats();

private:

protected:
	int maxHealth;
	int health;
	int strength;
	int lives;
	//Box hitBox;
	//AiMode mode;
	//AssignedAiMode AMode;
	float maxCrawlSpeed;
	float maxWalkSpeed;
	float maxRunSpeed;
	float maxSpeed;
	bool inUse;
};
