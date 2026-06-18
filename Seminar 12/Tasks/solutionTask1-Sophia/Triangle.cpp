#include "Triangle.h"
#include <stdexcept>

Triangle::Triangle(double px, double py, double ppx, double ppy, double pppx, double pppy) : p1x(px), p1y(py), p2x(ppx), p2y(ppy), p3x(pppx), p3y(pppy)
{
    double sideA = getSideA();
    double sideB = getSideB();
    double sideC = getSideC();

    if (sideA + sideB <= sideC || sideA + sideC <= sideB || sideC + sideB <= sideA) {
        throw std::invalid_argument("doesn't meet triangle criteria");
    }
}

double Triangle::getSideA() const
{
    return sqrt((p2x - p3x) * (p2x - p3x) + (p2y - p3y) * (p2y - p3y));
}

double Triangle::getSideB() const
{
    return sqrt((p1x - p3x) * (p1x - p3x) + (p1y - p3y) * (p1y - p3y));
}

double Triangle::getSideC() const
{
    return sqrt((p1x - p2x) * (p1x - p2x) + (p1y - p2y) * (p1y - p2y));
}

double Triangle::solveArea() const
{
    double halfP = solvePerimeter() / 2;
    double sideA = getSideA();
    double sideB = getSideB();
    double sideC = getSideC();
    return sqrt(halfP * (halfP - sideA) * (halfP - sideB) * (halfP - sideC));
}

double Triangle::solvePerimeter() const
{
    return getSideA() + getSideB() + getSideC();
}

double Triangle::area(double x1, double y1, double x2, double y2, double x3, double y3) const 
{
    return std::abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) / 2.0);
}

bool Triangle::isPointFromShape(double x, double y) const
{
    double total = area(p1x, p1y, p2x, p2y, p3x, p3y);

    double a1 = area(x, y, p2x, p2y, p3x, p3y);
    double a2 = area(p1x, p1y, x, y, p3x, p3y);
    double a3 = area(p1x, p1y, p2x, p2y, x, y);
    
    return std::abs(total - (a1 + a2 + a3)) < epsilon;
}
