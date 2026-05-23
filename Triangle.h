#pragma once
#include "Shape.h"

class Triangle : public Shape
{
private:
	double x1, y1, x2, y2, x3, y3;
public:
	double triangleArea(double x1, double y1, double x2, double y2, double x3, double y3) const;
	Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
	double area() const override;
	double perimeter() const override;
	bool isIn(double x, double y) const override;
	std::unique_ptr<Shape> clone() const override;

};