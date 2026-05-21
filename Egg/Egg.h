#ifndef EGG_EGG_H
#define EGG_EGG_H
#include <iostream>

class Egg {
    std::string name;
    double health;
    double attackDamage;
    double armor;
    double criticalStrike;
    int fightCount;
public:
    Egg(std::string name, double health, double attackDamage, double armor, double criticalStrike);
    std::string getName() const;
    double getHealth() const;
    double getAttackDamage() const;
    double getArmor() const;
    double getCriticalStrike() const;
    void takeDamage(double damage);
    bool isThirdFight() const;
    void updateFightCount();
};

#endif //EGG_EGG_H
