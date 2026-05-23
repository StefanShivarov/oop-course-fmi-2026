#pragma once
#include <string>

#include "Mage.h"
#include "Tank.h"
#include "Warrior.h"

class Item {
public:
    Item(const std::string& name, double effectValue);
    virtual ~Item() = default;

    const std::string& getName() const;
    double getEffectValue() const;

    virtual void applyToTank(Tank& tank) const = 0;
    virtual void applyToWarrior(Warrior& warrior) const = 0;
    virtual void applyToMage(Mage& mage) const = 0;

    // virtual std::unique_ptr<Item> clone() const = 0;

protected:
    static void heal(Character& character, double amount);
    static void increaseMaxHealth(Character& character, double amount);
    static void increaseAttackDamage(Character& character, double amount);
    static void increaseAbilityPower(Character& character, double amount);
    static void restoreMana(Mage& mage, double amount);
    static void increaseMaxMana(Mage& mage, double amount);

    double effectValue = 0.0;

private:
    std::string name;
};
