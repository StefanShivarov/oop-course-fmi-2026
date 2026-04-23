#include "EggTournament.h"

void EggTournament::addEgg(const Egg& egg)
{
	if (!fighter.hasValue())
	{
		fighter.setValue(egg);
	}
	else
	{
		waitingEggs.push(egg);
	}
}

void EggTournament::playNextBattle()
{

	if (!hasNextBattle()) return;
	Egg opponent = waitingEggs.peek();
	waitingEggs.pop();
	Egg current = fighter.getValue();
	current.attack(opponent);
	if (opponent.isAlive())
	{
		opponent.attack(current);
	}
	if (!current.isAlive())
	{
		fighter.setValue(opponent);
	}
}

Optional<Egg> EggTournament::getCurrentFighter() const
{
	return fighter;
}

bool EggTournament::hasNextBattle() const
{
	return fighter.hasValue()&& !waitingEggs.isEmpty();
}
