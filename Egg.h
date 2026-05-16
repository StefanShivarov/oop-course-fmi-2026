#pragma once
#include<string>
using std::string;

class Egg
{
private:
	string name;
	int health = 0;
	int damage = 0;
	int armor = 0;
	int criticalStrike = 0;
	int countFights = 0;

public:
	Egg() = default;
	Egg(const string& name, int health, int damage, int armor, int criticalStrike);

	const string& getName()const;
	int getHealth()const;
	int getDamage()const;
	int getArmor()const;
	int getCriticalStrike()const;

	bool isAlive()const;
	int attack();
	void takeDamage(int incomingDamage);
};

