#include "Circle.h"
#include <stdexcept>
Circle::Circle(double x, double y, double r) : centerX(x), centerY(y), radius(r)
{
    if (radius <= 0) {
        throw std::invalid_argument("radius can't be < 0");
    }
}

double Circle::solveArea() const
{
    return PI * radius * radius;
}

double Circle::solvePerimeter() const
{
    return PI * radius * 2;
}

bool Circle::isPointFromShape(double x, double y) const
{
    double dx = x - centerX;
    double dy = y - centerY;
    return (dx * dx + dy * dy) <= (radius * radius);
}
