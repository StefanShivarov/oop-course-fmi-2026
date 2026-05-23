#include "Triangle.h"
#include <cmath>
double Triangle::triangleArea(double x1, double y1, double x2, double y2, double x3, double y3) const
{
	return std::abs(
		x1 * (y2 - y3) +
		x2 * (y3 - y1) +
		x3 * (y1 - y2)
	) / 2.0;
}
Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3):x1(x1),y1(y1),x2(x2), y2(y2), x3(x3), y3(y3)
{
}

double Triangle::area() const
{
	//double s1 = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	//double s2 = sqrt(pow((x3 - x2), 2) + pow((y3 - y2), 2));
	//double s3 = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
	//double p = (s1 + s2 + s3) / 2;
	//return sqrt(p * (p - s1) * (p - s2) * (p - s3));
	return triangleArea(x1, y1, x2, y2, x3, y3);
}

double Triangle::perimeter() const
{
	double s1 = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	double s2 = sqrt(pow((x3 - x2), 2) + pow((y3 - y2), 2));
	double s3 = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));

	return s1 + s2 + s3;
}


	bool Triangle::isIn(double x, double y) const
	{
		double A = area();

		double A1 = triangleArea(x, y, x2, y2, x3, y3);

		double A2 = triangleArea(x1, y1, x, y, x3, y3);

		double A3 = triangleArea(x1, y1, x2, y2, x, y);

		return std::abs(A - (A1 + A2 + A3)) < 0.0001;
	}

	std::unique_ptr<Shape> Triangle::clone() const
	{
		return std::make_unique<Triangle>(*this);
	}


