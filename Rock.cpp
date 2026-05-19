#include "Rock.h"

int Rock::play(const Player& other) const {
	return other.playAgainstRock(*this);
}
int Rock::playAgainstRock(const Rock& other) const {
	return 0;
}
int Rock::playAgainstPaper(const Paper& other) const {
	return 1;

}
int Rock::playAgainstScissors(const Scissors& other) const {
	return -1;
}
