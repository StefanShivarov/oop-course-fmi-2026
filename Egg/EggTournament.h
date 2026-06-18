#ifndef EGG_EGGTOURNAMENT_H
#define EGG_EGGTOURNAMENT_H
#include <queue>

#include "Egg.h"


class EggTournament {
    std::queue<Egg> eggs;
    std::optional<Egg> currentFighter;
public:
    void addEgg(Egg egg);
    template <typename... Eggs> void addEggs(const Eggs&... eggs_);
    void playNextBattle();
    std::optional<Egg> getCurrentFighterEgg();
    bool hasNextFight();
};

template<typename ... Eggs>
void EggTournament::addEggs(const Eggs&...eggs_) {
    (addEgg(eggs_), ...);
}


#endif //EGG_EGGTOURNAMENT_H
