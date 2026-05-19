#pragma once
#include "Shape.h"
class Rectangle : public Shape
{
private:
	Point bottomLeft;
	Point TopRight;
public:
	Rectangle(const std::string& label, const Point& bL, const Point& tR) :
		Shape(label),
		bottomLeft(Point(std::min(bL.getX(), tR.getX()), std::min(bL.getY(),tR.getY()))),
		TopRight(Point(std::max(bL.getX(), tR.getX()), std::max(bL.getY(), tR.getY()))) {
		if (bL == tR )
		{
			throw std::invalid_argument("Sides are 0");
		}
	}
	std::string getType() const override {
		return "Rectangle";
	}
	double getArea() const override {
		return abs((TopRight.getX() - bottomLeft.getX()) * (TopRight.getY() - bottomLeft.getY()));
	}
	double getPerimeter() const override {
		return 2 * abs((TopRight.getX() - bottomLeft.getX()) + (TopRight.getY() - bottomLeft.getY()));
	}
	bool isPointInside(const Point& p) const override{
		return p.getX() >= bottomLeft.getX() && p.getX() <= TopRight.getX() && p.getY() >= bottomLeft.getX() && p.getY() <= TopRight.getY();
	}
	std::unique_ptr<Shape> clone() const override {
		return std::make_unique<Rectangle>(*this);
	}
};

