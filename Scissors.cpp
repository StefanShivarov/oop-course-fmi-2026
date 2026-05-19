#include "Scissors.h"

int Scissors::play(const Player& other) const {
	return other.playAgainstScissors(*this);
}
int Scissors::playAgainstRock(const Rock& other) const {
	return 1;
}
int Scissors::playAgainstPaper(const Paper& other) const {
	return -1;

}
int Scissors::playAgainstScissors(const Scissors& other) const {
	return 0;
}