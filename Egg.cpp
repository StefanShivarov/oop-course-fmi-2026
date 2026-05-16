#include "Egg.h"

Egg::Egg(const string& name, int health, int damage, int armor,
	int criticalStrike) :name(name), health(health), damage(damage), 
	armor(armor), criticalStrike(criticalStrike) {}

const string& Egg::getName()const
{
	return name;
}

int Egg::getHealth()const
{
	return health;
}

int Egg::getArmor()const
{
	return armor;
}

int Egg::getDamage()const
{
	return damage;
}

int Egg::getCriticalStrike()const
{
	return criticalStrike;
}

bool Egg::isAlive()const
{
	return health > 0;
}

int Egg::attack()
{
	countFights++;
	int totalDamage = damage;

	if (countFights % 3 == 0)
	{
		totalDamage += criticalStrike;
	}

	return totalDamage;
}

void Egg::takeDamage(int incomingDamage)
{
	int remainingDamage = incomingDamage;

	if (armor > 0)
	{
		int absorbed = std::min(remainingDamage, armor);
		armor -= absorbed;
		remainingDamage -= absorbed;
	}
	health -= remainingDamage;

	if (health < 0)
	{
		health = 0;
	}
}