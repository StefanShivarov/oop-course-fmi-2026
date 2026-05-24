#include "Paper.h"

int Paper::playAgainst(const Player& other) const
{
    return -other.againstPaper(*this);
}


int Paper::againstRock(const Rock& r) const
{
    return 1;
}

int Paper::againstPaper(const Paper& p) const
{
    return 0;
}

int Paper::againstScissors(const Scissors& s) const
{
    return -1;
}
