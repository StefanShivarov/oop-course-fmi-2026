#include "AbilityPowerBoostItem.h"
#include "DamageBoostItem.h"
#include "HealthPotion.h"
#include "Mage.h"
#include "ManaPotion.h"
#include "MaxHealthBoostItem.h"
#include "MaxManaBoostItem.h"
#include "Tank.h"
#include "Warrior.h"

#include <iostream>
void printCharacterStats(const Character& character) {
    std::cout << "Name: " << character.getName()
        << ", Health: " << character.getHealth() << "/" << character.getMaxHealth()
        << ", Attack Damage: " << character.getAttackDamage()
        << ", Ability Power: " << character.getAbilityPower()
        << std::endl;
}

void printCharacterStats(const Mage& mage) {
    std::cout << "Name: " << mage.getName()
        << ", Health: " << mage.getHealth() << "/" << mage.getMaxHealth()
        << ", Attack Damage: " << mage.getAttackDamage()
        << ", Ability Power: " << mage.getAbilityPower()
        << ", Mana: " << mage.getMana() << "/" << mage.getMaxMana()
        << std::endl;
}

int main()
{
    Tank tank("Serhan", 1200.0, 80.0, 20.0);
    Mage mage("Emil", 500.0, 25.0, 120.0, 1000.0);
    Warrior warrior("Stef", 900.0, 140.0, 10.0);

    HealthPotion healthPotion("Small Health Potion", 0.25);
    ManaPotion manaPotion("Ancient Mana Potion", 0.40);
    DamageBoostItem damageBoost("Sharpening Stone", 0.20);
    AbilityPowerBoostItem abilityPowerBoost("Enchanted Amulet", 0.20);
    MaxHealthBoostItem maxHealthBoost("Vitality Stone", 0.10);
    MaxManaBoostItem maxManaBoost("Mana Crystal", 0.25);

    std::cout << "Before using items:\n";
    printCharacterStats(tank);
    printCharacterStats(mage);
    printCharacterStats(warrior);

    // the potions won't do anything right now since characters are already at max hp and max mana

    std::cout << "\nUsing health potion:\n";

    tank.useItem(healthPotion);
    mage.useItem(healthPotion);
    warrior.useItem(healthPotion);

    printCharacterStats(tank);
    printCharacterStats(mage);
    printCharacterStats(warrior);

    std::cout << "\nUsing mana potion:\n";
    tank.useItem(manaPotion);
    mage.useItem(manaPotion);
    warrior.useItem(manaPotion);

    printCharacterStats(tank);
    printCharacterStats(mage);
    printCharacterStats(warrior);

    std::cout << "\nUsing damage boost item:\n";
    tank.useItem(damageBoost);
    mage.useItem(damageBoost);
    warrior.useItem(damageBoost);

    printCharacterStats(tank);
    printCharacterStats(mage);
    printCharacterStats(warrior);

    std::cout << "\nUsing ability power boost item:\n";
    tank.useItem(abilityPowerBoost);
    mage.useItem(abilityPowerBoost);
    warrior.useItem(abilityPowerBoost);

    printCharacterStats(tank);
    printCharacterStats(mage);
    printCharacterStats(warrior);

    std::cout << "\nUsing max health boost item:\n";
    tank.useItem(maxHealthBoost);
    mage.useItem(maxHealthBoost);
    warrior.useItem(maxHealthBoost);

    printCharacterStats(tank);
    printCharacterStats(mage);
    printCharacterStats(warrior);

    std::cout << "\nUsing max mana boost item:\n";
    tank.useItem(maxManaBoost);
    mage.useItem(maxManaBoost);
    warrior.useItem(maxManaBoost);

    printCharacterStats(tank);
    printCharacterStats(mage);
    printCharacterStats(warrior);
}
