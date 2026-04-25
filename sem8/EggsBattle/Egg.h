#pragma once
#include <string>
#include <iostream>

class Egg
{
	std::string name;
	int health = 0;
	int damage = 0;
	int armor = 0;
	int criticalStrike = 0;

	size_t battlesCount = 0;

public:
	Egg() = default;
	Egg(std::string name, int health, int damage, int armor, int criticalStrike);

	void takeDamage(int damage);
	bool isAlive() const;
	void attack(Egg& opponent);

	friend std::ostream& operator<<(std::ostream& os, const Egg& egg);

};
