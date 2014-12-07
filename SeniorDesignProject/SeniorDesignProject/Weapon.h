#pragma once
class Weapon
{
public:
	void Init();
	float getRange();
	void setRange(float range);
	float getSpread();
	void setSpread(float spread);
	float getAccuracy();
	void setAccuracy(float accuracy);
	float getAttack();
	void setAttack(float attackDmg);
	float getMelee();
	void setMelee(float meleeDmg);
	float getDefend();
	void setDefend(float defenceRating);
	int getReloadTime();
	void setReloadTime(int reloadTime);
	int getMagSize();
	void setMagSize(int magSize);
	void setExtraClips(int clips);
	int getExtraClips();
	void reload();
	Weapon();
	~Weapon();

private:

protected:
	float range; //Fire cone length
	float spread; //Fire cone radius
	float accuracy; //Fire cone random tilt
	float attack;
	float meleeAttack;
	float defend;
	int reloadTime; //In milliseconds
	int magSize; //Magazine capacity
	int extraMags;
};

