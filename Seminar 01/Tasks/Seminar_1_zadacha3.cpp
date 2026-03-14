

#include <iostream>

namespace Triangles {
    struct Point {
        double x;
        double y;
    };

    struct Triangle {
        Point a;
        Point b;
        Point c;
    };

    double myabs(const double a) {
        return a >= 0 ? a : -a;
    }

    double findArea(const Triangle& t) {
        return myabs(t.a.x * (t.b.y - t.c.y) + t.b.x * (t.c.y - t.a.y) + t.c.x * (t.a.y - t.b.y)) / 2.0;
    }

    void sortedTriangles(Triangle triangle[], const int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 1 - i; j++) {
                if (findArea(triangle[j]) > findArea(triangle[j + 1])) {
                    Triangle temp = triangle[j];
                    triangle[j] = triangle[j + 1];
                    triangle[j + 1] = temp;
                }
            }
        }
    }

    void printTriangles(const Triangle triangle[], const int n) {
        const double epsilon = 0.00001;
        for (int i = 0; i < n; i++) {
            std::cout << "Triangle cords: (" << triangle[i].a.x << ' ' << triangle[i].a.y << ") " <<
                '(' << triangle[i].b.x << ' ' << triangle[i].b.y << ") " <<
                '(' << triangle[i].c.x << ' ' << triangle[i].c.y << ") ";
            if (findArea(triangle[i]) < epsilon) {
                std::cout << " All points are on the same line\n";
            }
            else
                std::cout << "Triangle area: " << findArea(triangle[i]) << '\n';
        }
    }
}

int main()
{
    using namespace Triangles;

    int n;
    std::cin >> n;

    if (n <= 0)
        return 0;

    Triangle* triangles = new Triangle[n];

    for (int i = 0; i < n; i++) {
        std::cin >> triangles[i].a.x >> triangles[i].a.y;
        std::cin >> triangles[i].b.x >> triangles[i].b.y;
        std::cin >> triangles[i].c.x >> triangles[i].c.y;
    }

    sortedTriangles(triangles, n);
    printTriangles(triangles, n);

    delete[] triangles;

    return 0;
}


