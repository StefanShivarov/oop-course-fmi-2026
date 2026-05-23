#pragma once
#include "Shape.h"
class Rectangle :public Shape
{
private:
	double x, y;
	double width;
	double heigth;

public:
	Rectangle(double x, double y, double width, double heigth);
	double area() const override;
	double perimeter() const override;
	bool isIn(double x1, double y1) const override;
	std::unique_ptr<Shape> clone() const override;

};