#pragma once
#include "Shape.h"
class Circle : public Shape
{
private:
	Point centre;
	double radius;
public:
	Circle(const std::string& label, const Point& centre, double radius) : Shape(label), centre(centre), radius(radius){
		if (radius <= 0)
		{
		 	throw std::invalid_argument("Radius must be a positive number");
		}
	}
	std::string getType() const override {
		return "Circle";
	}
	double getArea() const override {
		return PI * radius * radius;
	}
	double getPerimeter() const override {
		return 2 * PI * radius;
	}
	double calculateDistanceToPoint(const Point& p) const {
		return sqrt(((centre.getX() - p.getX()) * (centre.getX() - p.getX()) + ((centre.getY() - p.getY()) * (centre.getY() - p.getY()))));
	}
	bool isPointInside(const Point& p) const override {
		return calculateDistanceToPoint(p) <= radius;
	}
	std::unique_ptr<Shape> clone() const override {
		return std::make_unique<Circle>(*this);
	}
};

