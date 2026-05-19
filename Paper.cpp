#include "Paper.h"

int Paper::play(const Player& other) const {
	return other.playAgainstPaper(*this);
}
int Paper::playAgainstRock(const Rock& other) const {
	return -1;
}
int Paper::playAgainstPaper(const Paper& other) const {
	return 0;

}
int Paper::playAgainstScissors(const Scissors& other) const {
	return 1;
}
