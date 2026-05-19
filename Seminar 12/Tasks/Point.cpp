#include "Point.h"

bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}
