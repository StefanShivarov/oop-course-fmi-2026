#pragma once
#include <string>
#include <memory>

class Item;

class Character {
public:
    Character(const std::string& name, double maxHealth, double attackDamage, double abilityPower);
    virtual ~Character() = default;

    const std::string& getName() const;
    double getHealth() const;
    double getMaxHealth() const;
    double getAttackDamage() const;
    double getAbilityPower() const;

    virtual void useItem(const Item& item) = 0;
    // virtual std::unique_ptr<Character> clone() const = 0;

private:
    std::string name;
    double health = 0;
    double maxHealth = 0;
    double attackDamage = 0;
    double abilityPower = 0;

    friend class Item;
};
