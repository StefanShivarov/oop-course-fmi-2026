#include "Egg.h"
Egg::Egg()
{
}
Egg::Egg(const Egg &other)
{
    name = other.name;
    health = other.health;
    damage = other.damage;
    armor = other.armor;
    criticalStrike = other.criticalStrike;
}
Egg::Egg(std::string name, double health, double damage, double armor, double criticalStrike)
    : name(name), health(health), damage(damage), armor(armor), criticalStrike(criticalStrike)
{
}
double Egg::getHealth() const
{
    return health;
}
double Egg::getDamage() const
{
    return damage;
}
double Egg::getArmor() const
{
    return armor;
}
double Egg::getCriticalStrike() const
{
    return criticalStrike;
}
int Egg::getGamesPlayed() const
{
    return gamesPlayed;
}
std::string Egg::getName() const
{
    return name;
}
void Egg::takeDamage(double hit)
{
    if (armor > 0)
    {
        armor -= hit;
        if (armor < 0)
        {
            health += armor;
        }
    }
    else
    {
        health -= hit;
    }
}
void Egg::addOneToGamesPlayed()
{
    gamesPlayed++;
}