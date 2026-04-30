#pragma once
#include <iostream>
#include <string>
class Egg
{
private:
    std::string name;
    double health = 100;
    double damage = 30;
    double armor = 33;
    double criticalStrike = 50;
    int gamesPlayed = 0;

public:
    Egg();
    Egg(const Egg &other);
    Egg(std::string name, double health, double damage, double armor, double criticalStrike);
    double getHealth() const;
    double getDamage() const;
    double getArmor() const;
    double getCriticalStrike() const;
    int getGamesPlayed() const;
    std::string getName() const;
    void takeDamage(double damage);
    void addOneToGamesPlayed();
};