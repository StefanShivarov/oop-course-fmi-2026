#pragma once
#include <vector>
#include "Player.h"
class Tournament
{
private:
	std::vector<Player*> players;
public:
	void addPlayer(Player* player);
	Player* getWinner() const;
};

