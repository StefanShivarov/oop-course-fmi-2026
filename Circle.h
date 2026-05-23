#pragma once
#include "Shape.h"
class Circle: public Shape
{
private:
	double x;
	double y;
	double radius;
public:

	Circle(double x, double y, double radius);
	double area() const override;
	double perimeter() const override;
	bool isIn(double x1, double y1) const override;
	std::unique_ptr <Shape> clone() const override;

};