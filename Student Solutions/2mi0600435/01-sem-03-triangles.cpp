#include <iostream>
#include <cmath>

namespace Triangles {
	struct Point {
		double X;
		double Y;
	};

	struct Triangle {
		Point A;
		Point B;
		Point C;

		double calculateArea() const {
			double area = 0.5 * std::abs(A.X * (B.Y - C.Y) + B.X * (C.Y - A.Y) + C.X * (A.Y - B.Y));
			return area;
		}

		void print() const {
			std::cout << "Triangle:";
			std::cout << " (" << A.X << ", " << A.Y << "),";
			std::cout << " (" << B.X << ", " << B.Y << "),";
			std::cout << " (" << C.X << ", " << C.Y << ")";
			std::cout << " - Area: " << calculateArea() << std::endl;
		}
	};

	namespace Utils {
		void readTriangles(Triangle* triangles, int count) {
			for (int i = 0; i < count; i++) {
				std::cin >> triangles[i].A.X >> triangles[i].A.Y;
				std::cin >> triangles[i].B.X >> triangles[i].B.Y;
				std::cin >> triangles[i].C.X >> triangles[i].C.Y;
			}
		}

		bool compareByArea(const Triangle& t1, const Triangle& t2) {
			return t1.calculateArea() > t2.calculateArea();
		}

		void sortTriangle(Triangle* triangles, int count, bool (*comparator)(const Triangle&, const Triangle&)) {
			for (int i = 0; i < count - 1; i++) {
				for (int j = 0; j < count - i - 1; j++) {
					if (comparator(triangles[j], triangles[j + 1])) {
						Triangle temp = triangles[j];
						triangles[j] = triangles[j + 1];
						triangles[j + 1] = temp;
					}
				}
			}
		}

		void printTriangles(const Triangle* triangles, int count) {
			for (int i = 0; i < count; i++) {
				triangles[i].print();
			}
		}
	}
}

int main() {
	using namespace Triangles;
	int n;
	std::cin >> n;

	Triangle* triangles = new Triangle[n];

	Utils::readTriangles(triangles, n);
	Utils::sortTriangle(triangles, n, Utils::compareByArea);

	Utils::printTriangles(triangles, n);

	delete[] triangles;
}