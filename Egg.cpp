#include "Egg.h"
#include <cstring>
#include<iostream>


Egg::Egg(std::string name, unsigned health, int damage, int armor, int criticalStrike): 
	name(std::move(name)), health(health), damage(damage),armor(armor), criticalStrike(criticalStrike) {}




const std::string& Egg::getName() const
{ 
	return name;
}

unsigned Egg::getHealth() const
{
	return health;
}

int Egg::getDamage() const
{
	return damage;
}

int Egg::getArmor() const
{
	return armor;
}

int Egg::getCtiticalStrike() const
{
	return criticalStrike;
}

int Egg::getBattleCount() const
{
	return battleCount;
}

bool Egg::isAlive() const
{
	return health>0;
}

void Egg::setHealth(unsigned health)
{
	this->health = health;
}

void Egg::setArmor(int armor)
{
	this->armor = armor;
}

void Egg::attack(Egg& other)
{
	battleCount++;
	int totalDamage = damage;
	if (battleCount % 3 == 0)
	{
		totalDamage += criticalStrike;
	}
	 

	if (other.armor > 0) {
		other.armor -= totalDamage;
		if (other.armor < 0) {
			other.health += other.armor;
		}
	}
	else
	{
		other.health -= totalDamage;

	}
}
