#pragma once
#include "Shape.h"
class Triangle : public Shape
{
private:
	Point A;
	Point B;
	Point C;
	double sideAB;
	double sideAC;
	double sideBC;
public:
	Triangle(const std::string& label, const Point& A, const Point& B, const Point& C) : Shape(label), A(A), B(B), C(C) {
		sideAB = calculateSide(A, B);
		sideAC = calculateSide(A, C);
		sideBC = calculateSide(B, C);
		if (!isTriangle(A, B, C))
		{
			throw std::invalid_argument("Your points are on the same line");
		}
	}

	double calculateSide(const Point& p1, const Point& p2) {
		return sqrt(((p2.getX() - p1.getX()) * (p2.getX() - p1.getX())) + ((p2.getY() - p1.getY()) * (p2.getY() - p1.getY())));
	}

	bool isTriangle(const Point& A, const Point& B, const Point& C) {

		double sideAB = calculateSide(A, B);
		double sideAC = calculateSide(A, C);
		double sideBC = calculateSide(B, C);
		return (sideAB + sideAC > sideBC) && (sideAB + sideBC > sideAC) && (sideAC + sideBC > sideAB);
	}
	std::string getType() const override {
		return "Trinagle";
	}
	double getArea() const override {
		double p = (sideAB + sideAC + sideBC) / 2;
		return sqrt(p * (p - sideAB) * (p - sideAC) * (p - sideBC));
	}
	double getPerimeter() const override {
		return sideAB + sideAC + sideBC;
	}
	bool isPointInside(const Point& p) const override {
		double areaPAB = abs(p.getX() * (A.getY() - B.getY()) + A.getX() * (B.getY() - p.getY()) + B.getX() * (p.getY() - A.getY())) / 2;
		double areaPAC = abs(p.getX() * (A.getY() - C.getY()) + A.getX() * (C.getY() - p.getY()) + C.getX() * (p.getY() - A.getY())) / 2;
		double areaPCB = abs(p.getX() * (C.getY() - B.getY()) + C.getX() * (B.getY() - p.getY()) + B.getX() * (p.getY() - C.getY())) / 2;
		return getArea() == areaPAB + areaPAC + areaPCB;
	}
	std::unique_ptr<Shape> clone() const override {
		return std::make_unique<Triangle>(*this);
	}

};
 
