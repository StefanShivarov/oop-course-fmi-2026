#include "EggTournament.h"
#include <iostream>

void EggTournament::addEgg(const Egg& egg)
{
	if (!currentFighter.has_value()) {
		currentFighter = egg;
	}
	else {
		fightersQueue.push(egg);
	}
}

void EggTournament::addEggs(const std::vector<Egg>& eggs)
{
	for (size_t i = 0; i < eggs.size(); i++)
	{
		addEgg(eggs[i]);
	}
}

std::optional<Egg> EggTournament::getCurrentFighter()
{
	return currentFighter;
}

bool EggTournament::hasNextBattle()
{
	return fightersQueue.size();
}

void EggTournament::playNextBattle()
{
	if (fightersQueue.empty()) {
		std::cout << "No battles\n";
		return;
	}

	Egg opponent = fightersQueue.front();
	fightersQueue.pop();

	while (opponent.isAlive() && currentFighter->isAlive()) {
		currentFighter->attack(opponent);
		if (opponent.isAlive()) {
			opponent.attack(*currentFighter);
		}
	}

	if (opponent.isAlive()) {
		*currentFighter = opponent;
	}
}

