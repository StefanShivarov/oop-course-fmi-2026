#include "EggTournament.h"
#include<print>

void EggTournament::addEgg(const Egg& egg)
{
	if (!currentFighter.has_value())
	{
		currentFighter = egg;
	}
	else
	{
		opponents.push(egg);
	}
}

void EggTournament::addEggs(const vector<Egg>& eggs)
{
	for (size_t i = 0;i < eggs.size();i++)
	{
		addEgg(eggs[i]);
	}
}

bool EggTournament::hasNextBattle()const
{
	return currentFighter.has_value() && !opponents.empty();
}

const optional<Egg>& EggTournament::getCurrentFighter()const
{
	return currentFighter;
}

void EggTournament::playNextBattle()
{
	while (hasNextBattle())
	{
		Egg opponent = opponents.front();
		opponents.pop();

		Egg fighter = currentFighter.value();

		std::println("Battle between {} and {} :", fighter.getName(), opponent.getName());

		while (opponent.isAlive() && fighter.isAlive())
		{
			opponent.takeDamage(fighter.attack());

			if (!opponent.isAlive())
			{
				break;
			}

			fighter.takeDamage(opponent.attack());
		}

		if (fighter.isAlive())
		{
			std::println("The winner is {}!", fighter.getName());
			std::println();
			currentFighter = fighter;
		}
		else
		{
			std::println("The winner is {}!", opponent.getName());
			std::println();
			currentFighter = opponent;
		}
	}
}