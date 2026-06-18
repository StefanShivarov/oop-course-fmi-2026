#pragma once
#include "Shape.h"

class Triangle : public Shape {
protected:
    double p1x;
    double p1y;
    double p2x;
    double p2y;
    double p3x;
    double p3y;
    double const epsilon = 0.000001;
public:
    Triangle(double p1x, double p1y, double p2x, double p2y, double p3x, double p3y);
    double getSideA() const;
    double getSideB() const;
    double getSideC() const;
    double solveArea() const override;
    double solvePerimeter() const override;
    double area(double x1, double y1, double x2, double y2, double x3, double y3) const;
    bool isPointFromShape(double x, double y) const override;
};