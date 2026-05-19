#pragma once
class Point
{
private:
	double x, y;
public:
	Point(double x, double y) : x(x), y(y) {}
	Point(const Point& other) { 
		x = other.x;
		y = other.y; 
	}
	double getX() const { return x; }
	double getY() const { return y; }


};

bool operator==(const Point& lhs, const Point& rhs); 
		
	
	