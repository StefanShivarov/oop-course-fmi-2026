#pragma once
#include "Shape.h"

class Circle : public Shape {
protected:
    double centerX;
    double centerY;
    double radius;
    double const PI = 3.14;
public:
    Circle(double x, double y, double r);
    double solveArea() const override;
    double solvePerimeter() const override;
    bool isPointFromShape(double x, double y) const override;
};