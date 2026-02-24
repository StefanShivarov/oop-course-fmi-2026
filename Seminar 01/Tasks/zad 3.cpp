
#include <iostream>
#include <cmath>
using std::sqrt;
using std::cout;
using std::cin;
using std::swap;


namespace TriangleN
{
    struct Point {
        int x;
        int y;
	};

    struct Triangle {
        Point a;
        Point b;
        Point c;
	};

    double findSideLength(const Point& a, const Point& b)
    {
        return sqrt((b.x - a.x) * (b.x - a.x) +
            (b.y - a.y) * (b.y - a.y));
    }

    double findArea(const Triangle &triangle)
    {
        double a = findSideLength(triangle.a, triangle.b);
        double b = findSideLength(triangle.b, triangle.c);
        double c = findSideLength(triangle.c, triangle.a);
        double p = (a + b + c) / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
	}

    void sort(Triangle *triangle, int n) {
   
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if( findArea(triangle[j]) < findArea(triangle[minIdx])) {
                    minIdx = j;
                }
            }
            if (i != minIdx) swap(triangle[i], triangle[minIdx]);
        }

    }
    
    void printTriangles(const Triangle triangle[], int n) {
        for (int i = 0; i < n; i++) {
            cout << triangle[i].a.x << " " << triangle[i].a.y << " | "
                      << triangle[i].b.x << " " << triangle[i].b.y << " | "
				      << triangle[i].c.x << " " << triangle[i].c.y << '\n';
			cout << "Area: " << findArea(triangle[i]) << '\n';
        }
	}
}

int main()
{
	using namespace TriangleN;
    int n;
    cout << "Enter the number of triangles: ";
    cin >> n;
	Triangle* triangle = new Triangle[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter the coordinates of triangle " << i + 1 << " (x1 y1 x2 y2 x3 y3): ";
        cin >> triangle[i].a.x >> triangle[i].a.y
            >> triangle[i].b.x >> triangle[i].b.y
            >> triangle[i].c.x >> triangle[i].c.y;
    }
    sort(triangle, n);
    cout << "Triangles sorted by area:\n";
    printTriangles(triangle, n);
    delete[] triangle;
	return 0;
}

