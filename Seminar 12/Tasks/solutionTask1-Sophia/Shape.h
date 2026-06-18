#pragma once

class Shape {
public:
    virtual double solveArea() const = 0;
    virtual double solvePerimeter() const = 0;
    virtual bool isPointFromShape(double x, double y) const = 0;
    virtual ~Shape() = default;
};