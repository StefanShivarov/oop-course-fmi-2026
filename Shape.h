#pragma once
#include <memory>

class Shape
{
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual bool isIn(double x, double y) const = 0;
    virtual std::unique_ptr<Shape> clone() const = 0;
     virtual ~Shape() = default;
};