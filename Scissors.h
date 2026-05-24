#pragma once

#pragma once
#include "Player.h"
#include "Rock.h"
#include "Paper.h"

class Scissors : public Player
{
public:
	int playAgainst(const Player& other) const override;

	int againstRock(const Rock& r) const override;
	int againstPaper(const Paper& p) const override;
	int againstScissors(const Scissors& s) const override;
};