#include "Egg.h"
#include <iostream>

Egg::Egg(std::string name, int health, int damage, int armor, int criticalStrike)
	: name(name), health(health), damage(damage), armor(armor), criticalStrike(criticalStrike)
{
}

void Egg::takeDamage(int damage)
{
	if (damage > armor) {
		health -= (damage - armor);
		armor = 0;
	}
	else {
		armor -= damage;
	}

}

bool Egg::isAlive() const
{
	return health > 0;
}

void Egg::attack(Egg& opponent)
{
	battlesCount++;
	int totalDamage = this->damage;
	if (battlesCount % 3 == 0) {
		totalDamage += criticalStrike;
	}
	opponent.takeDamage(totalDamage);
}

std::ostream& operator<<(std::ostream& os, const Egg& egg)
{
	os << egg.name << ", " << egg.health << ", " << egg.damage << ", " << egg.armor << ", " << egg.criticalStrike << '\n';

	return os;
}
