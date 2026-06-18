#pragma once
#include "Shape.h"

class Rectangle : public Shape {
protected:
    double upperLeftX;
    double upperLeftY;
    double sideA; //width
    double sideB; //height
public:
    Rectangle(double x, double y, double side1, double side2);
    double solveArea() const override;
    double solvePerimeter() const override;
    bool isPointFromShape(double x, double y) const override;
};