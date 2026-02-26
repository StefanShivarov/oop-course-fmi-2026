#include <iostream>

using std::cin;
using std::cout;

namespace Points {
    struct Point {
        int x = 0;
        int y = 0;
    };

    void readPoint(Point& point) {
        cin >> point.x >> point.y;
    }

    double getDistanceBetweenPoints(const Point& p1, const Point& p2) {
        int dx = p1.x - p2.x;
        int dy = p1.y - p2.y;
        return sqrt(dx * dx + dy * dy);
    }

    void printPoint(const Point& point) {
        cout << '(' << point.x << ", " << point.y << ") ";
    }
}

namespace Triangles {
    using namespace Points;

    struct Triangle {
        Point p1;
        Point p2;
        Point p3;
        // or alternatively Point points[3];
    };

    void readTriangle(Triangle& triangle) {
        readPoint(triangle.p1);
        readPoint(triangle.p2);
        readPoint(triangle.p3);
    }

    double getTrianglePerimeter(const Triangle& triangle) {
        double a = getDistanceBetweenPoints(triangle.p1, triangle.p2);
        double b = getDistanceBetweenPoints(triangle.p1, triangle.p3);
        double c = getDistanceBetweenPoints(triangle.p2, triangle.p3);
        return a + b + c;
    }

    double getTriangleArea(const Triangle& triangle) {
        double a = getDistanceBetweenPoints(triangle.p1, triangle.p2);
        double b = getDistanceBetweenPoints(triangle.p1, triangle.p3);
        double c = getDistanceBetweenPoints(triangle.p2, triangle.p3);
        double halfPer = (a + b + c) / 2;

        return sqrt(halfPer * (halfPer - a) * (halfPer - b) * (halfPer - c));
    }

    void sortTrianglesByMetric(Triangle* triangles, size_t n, double (*calculationMetric)(const Triangle&)) {
        double* metrics = new double[n];
        for (size_t i = 0; i < n; i++) {
            metrics[i] = calculationMetric(triangles[i]);
        }

        for (size_t i = 0; i < n - 1; i++) {
            size_t minAreaIndex = i;

            for (size_t j = i; j < n; j++) {
                if (metrics[j] < metrics[minAreaIndex]) {
                    minAreaIndex = j;
                }
            }

            if (minAreaIndex != i) {
                std::swap(triangles[i], triangles[minAreaIndex]);
                std::swap(metrics[i], metrics[minAreaIndex]);
            }
        }

        delete[] metrics;
    }

    void printTriangle(const Triangle& triangle) {
        printPoint(triangle.p1);
        printPoint(triangle.p2);
        printPoint(triangle.p3);
    }
}

int main() {
    using namespace Triangles;
    size_t n;
    cin >> n;

    Triangle* triangles = new Triangle[n];
    for (size_t i = 0; i < n; i++) {
        readTriangle(triangles[i]);
    }

    // sort by area
    sortTrianglesByMetric(triangles, n, [](const Triangle& t) { return getTriangleArea(t); });
    
    for (size_t i = 0; i < n; i++) {
        printTriangle(triangles[i]);
        cout << '\n';
    }

    // if you want to sort by perimeter
    // sortTrianglesByMetric(triangles, n, [](const Triangle& t) { return getTrianglePerimeter(t); });

    delete[] triangles;
}
