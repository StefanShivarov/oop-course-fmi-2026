#pragma once

class Player
{
protected:
public:
	virtual ~Player()= default;
	virtual int playAgainst(const Player& other) const = 0;
	virtual int againstRock(const class Rock&) const = 0;
	virtual int againstPaper(const class Paper&) const = 0;
	virtual int againstScissors(const class Scissors&) const = 0;
};