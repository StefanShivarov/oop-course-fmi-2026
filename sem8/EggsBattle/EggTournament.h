#pragma once
#include "Egg.h"
#include <string>
#include <vector>
#include <optional>
#include <queue>

class EggTournament
{
	std::queue<Egg> fightersQueue;
	std::optional<Egg> currentFighter;

public:
	EggTournament() = default;

	void addEgg(const Egg& egg);
	void addEggs(const std::vector<Egg>& eggs);
	void playNextBattle();
	std::optional<Egg> getCurrentFighter();
	bool hasNextBattle();
};

