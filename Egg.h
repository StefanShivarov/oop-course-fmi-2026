#pragma once
#include <string>

class Egg
{

private:
	std::string name;
	unsigned health;
	int damage;
	int armor;
	int criticalStrike;
	int battleCount=0;

	//void copyFrom(const Egg& other);
	//void moveFrom(Egg&& other) noexcept;
	//void free();

public:
	Egg(std::string name, unsigned health, int damage, int armor, int criticalStrike);

	/*Egg(const Egg& other);
	Egg& operator=(const Egg& other);

	Egg(Egg&& other) noexcept;
	Egg& operator=(Egg&& other) noexcept;

	~Egg();*/

	const std::string& getName() const;
	unsigned getHealth() const;
	int getDamage() const;
	int getArmor() const;
	int getCtiticalStrike() const;
	int getBattleCount() const;

	bool isAlive()const ;


	void setHealth(unsigned health);
	void setArmor(int armor);


	void attack( Egg& other);
};
