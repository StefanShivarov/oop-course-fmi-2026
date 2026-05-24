#include "Scissors.h"

int Scissors::playAgainst(const Player& other) const
{
    return -other.againstScissors(*this);
}


int Scissors::againstRock(const Rock& r) const
{
    return -1;
}

int Scissors::againstPaper(const Paper& p) const
{
    return 1;
}

int Scissors::againstScissors(const Scissors& s) const
{
    return 0;
}
