#include "RPSTournament .h"

void RPSTournament::addPlayer(std::unique_ptr<Player> p)
{
	players.push_back(std::move(p));
}

std::unique_ptr<Player> RPSTournament::run()
{
	std::vector<int> scores(players.size(),0);


	for (size_t i = 0; i < players.size(); i++)
	{
		for (size_t j = i+1; j < players.size(); j++)
		{
			int res = players[i]->playAgainst(*players[j]);
			scores[i] += res;
			scores[j] -= res;
		}
	}
	size_t best=0;
	for (size_t i = 1; i < players.size(); i++)
	{
		if (scores[i] > scores[best]) best = i;
	}
	return std::move(players[best]);
}
