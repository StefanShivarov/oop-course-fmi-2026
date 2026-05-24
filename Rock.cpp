#include "Rock.h"

int Rock::playAgainst(const Player& other) const
{
    return -other.againstRock(*this) ;
}

int Rock::againstRock(const Rock& r) const
{
    return 0;
}

int Rock::againstPaper(const Paper& p) const
{
    return -1;
}

int Rock::againstScissors(const Scissors& s) const
{
    return 1;
}
