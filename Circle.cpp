#include "Circle.h"
#include <numbers>
#include <cmath>
#include <stdexcept>

Circle::Circle(double x, double y, double radius):x(x), y(y), radius(radius)
{
    if (radius <= 0)
    {
        throw std::invalid_argument("Radius must be above 0");
    }
}

double Circle::area() const
{
    return std::numbers::pi * radius * radius;
}
double Circle::perimeter() const
{
    return 2 * std::numbers::pi * radius;
}

bool Circle::isIn(double x1, double y1) const
{
    double length = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
    return length <= radius;
}

std::unique_ptr<Shape> Circle::clone() const
{
    return std::make_unique<Circle>(*this);
}
