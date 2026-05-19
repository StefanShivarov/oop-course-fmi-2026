#pragma once
#include "Player.h"
class Paper:public Player
{
public:
	int play(const Player& other) const override;
	int playAgainstRock(const Rock& other) const override;
	int playAgainstPaper(const Paper& other) const override;
	int playAgainstScissors(const Scissors& other) const override;
};

