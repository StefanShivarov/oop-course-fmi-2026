#pragma once
#include "Egg.h"
#include"Queue.hpp"
#include "Optional.hpp"

class EggTournament
{
private:
	Queue<Egg> waitingEggs;
	Optional<Egg> fighter;

public:
	void addEgg(const Egg& egg);
	template<typename... Args>
	void addEggs(Args&&...args);
	void playNextBattle();
	Optional<Egg> getCurrentFighter()const;
	bool hasNextBattle()const;
};

template<typename ...Args>
inline void EggTournament::addEggs(Args && ...args)
{
	(addEgg(std::forward<Args>(args)), ...);
}
