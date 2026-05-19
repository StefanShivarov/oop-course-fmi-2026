#pragma once
#include "Point.h"
#include <string>
#include <iostream>
#include <cmath>
const double PI = 3.14159;
class Shape
{
protected: 
	std::string label;
public:
	Shape(const std::string& label) :label(label){}
	virtual ~Shape() {};

	virtual std::string getType() const = 0;
	virtual double getArea() const = 0;
	virtual double getPerimeter() const = 0;
	virtual bool isPointInside(const Point& p) const = 0;
	void printInfo() const {
		std::cout << "Shape: " << getType()
			<< " |Area: " << getArea()
			<< " |Perimeter: " << getPerimeter() << "\n";
	}
	virtual std::unique_ptr<Shape> clone() const = 0;
};

