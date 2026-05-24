#pragma once
#include "Player.h"
#include "Paper.h"
#include "Scissors.h"

class Rock : public Player
{
public:
	int playAgainst(const Player& other) const override;

	int againstRock(const Rock& r) const override;
	int againstPaper(const Paper& p) const override;
	int againstScissors(const Scissors& s) const override;
};