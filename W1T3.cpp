#include <iostream>
struct Point
{
	double x = 0;
	double y = 0;
};

struct Triangle
{
	Point A;
	Point B;
	Point C;
	double S = 0;
	double AbsoluteValue(double a) {
		if (a > 0) {
			return a;
		}
		else {
			return 0 - a;
		}
	}

	void calculate() {
		double temp = A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y);
		S = AbsoluteValue((temp)) / 2.0;
	}

	
	
};
Triangle* EnterTriangles(int n) {
	Triangle* triangles = new Triangle[n]{};
	for (int i = 0; i < n; i++) {
		double x1, y1, x2, y2, x3, y3;
		std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
		triangles[i].A.x = x1;
		triangles[i].A.y = y1;

		triangles[i].B.x = x2;
		triangles[i].B.y = y2;

		triangles[i].C.x = x3;
		triangles[i].C.y = y3;
		triangles[i].calculate();
	}
	return triangles;
}
void Sort(Triangle* triangles, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (triangles[j].S > triangles[j + 1].S) {
				Triangle temp = triangles[j + 1];
				triangles[j + 1] = triangles[j];
				triangles[j] = temp;
			}
		}
	}
}
void PrintT(const Triangle* triangles, const int size) {
	for (int i = 0; i < size; i++) {
		std::cout << (i + 1) << " S = " << triangles[i].S << std::endl;
	}
}

int main()
{
	int n;
	std::cin >> n;
	Triangle* result = EnterTriangles(n);
	Sort(result, n);
	PrintT(result, n);
	delete[] result;
}