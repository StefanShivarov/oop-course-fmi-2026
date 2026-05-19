#pragma once
class Rock;
class Paper;
class Scissors;

class Player
{
	public:
		virtual ~Player() = default;
		virtual int play(const Player& other) const = 0;
		virtual int playAgainstRock(const Rock& other)const = 0;
		virtual int playAgainstPaper(const Paper& other) const = 0;
		virtual int playAgainstScissors(const Scissors& other) const = 0;
};

