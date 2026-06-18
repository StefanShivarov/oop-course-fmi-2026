#include "Rectangle.h"
#include <stdexcept>

Rectangle::Rectangle(double x, double y, double side1, double side2) : upperLeftX(x), upperLeftY(y), sideA(side1), sideB(side2)
{
    if (sideA <= 0 || sideB <= 0) {
        throw std::invalid_argument("sides shouldn't be less than 0");
    }
}

double Rectangle::solveArea() const
{
    return sideA*sideB;
}

double Rectangle::solvePerimeter() const
{
    return 2 * (sideA+sideB);
}

bool Rectangle::isPointFromShape(double x, double y) const
{
    return (x >= upperLeftX && x <= upperLeftX + sideA && y >= upperLeftY && y <= upperLeftY+sideB);
}
