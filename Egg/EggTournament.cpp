#include "EggTournament.h"

void EggTournament::addEgg(Egg egg) {
    eggs.push(std::move(egg));
}

void EggTournament::playNextBattle() {
    if (hasNextFight()) {
        if (!getCurrentFighterEgg()) {
            currentFighter = std::move(eggs.front());
            eggs.pop();
        }
        currentFighter -> updateFightCount();
        eggs.front().updateFightCount();
        while (true) {
            std::println("A HP: {}", currentFighter->getHealth());
            std::println("B HP: {}", eggs.front().getHealth());
            eggs.front().takeDamage(currentFighter -> getAttackDamage());
            if (currentFighter -> isThirdFight()) {
                eggs.front().takeDamage(currentFighter -> getCriticalStrike());
            }

            if (eggs.front().getHealth() <= 0) {
                eggs.pop();
                break;
            }

            currentFighter -> takeDamage(eggs.front().getAttackDamage());
            if (eggs.front().isThirdFight()) {
                currentFighter -> takeDamage(eggs.front().getCriticalStrike());
            }

            if (currentFighter -> getHealth() <= 0) {
                currentFighter = std::move(eggs.front());
                eggs.pop();
                break;
            }
        }
        std::println("winner : {}", currentFighter -> getName());
    }
    else {
        std::println("No more fights!");
    }
}

std::optional<Egg> EggTournament::getCurrentFighterEgg() {
    return currentFighter;
}

bool EggTournament::hasNextFight() {
    return (!eggs.empty() && getCurrentFighterEgg()) || eggs.size() >= 2;
}
