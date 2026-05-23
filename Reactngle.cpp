#include "Reactngle.h"
#include <stdexcept>

Rectangle::Rectangle(double x, double y, double width, double heigth): x(x), y(y), width(width), heigth(heigth)
{
	if(width<=0||heigth<=0) throw std::invalid_argument("sides must be positive");
}

double Rectangle::area() const
{
	return width* heigth;
}

double Rectangle::perimeter() const
{
	return 2*(width+ heigth);
}

bool Rectangle::isIn(double x1, double y1) const
{
	if (x1<x || x1> x + width || y1<y || y1>y + heigth) return false;
	return true;
}

std::unique_ptr<Shape> Rectangle::clone() const
{
	return std::make_unique<Rectangle>(*this);
}
