#include <iostream>
using std::cin;
using std::cout;

struct Triangle {
    int pointAx = 0;
    int pointAy = 0;
    int pointBx = 0;
    int pointBy = 0;
    int pointCx = 0;
    int pointCy = 0;
};

void readTriangle(Triangle& triangle) {
    cout << "Enter the coordinates of point A of the triangle (x y): \n";
    cin >> triangle.pointAx >> triangle.pointAy;
    cout << "Enter the coordinates of point B of the triangle (x y): \n";
    cin >> triangle.pointBx >> triangle.pointBy;
    cout << "Enter the coordinates of point C of the triangle (x y): \n";
    cin >> triangle.pointCx >> triangle.pointCy;
}

double absValue(double value) {
    return value < 0 ? -value : value;
}

void swapTriangles(Triangle& t1, Triangle& t2) {
    Triangle temp = t1;
    t1 = t2;
    t2 = temp;
}

double triangleArea(const Triangle& triangle) {
    double sum = (triangle.pointAx * (triangle.pointBy - triangle.pointCy) +
        triangle.pointBx * (triangle.pointCy - triangle.pointAy) +
        triangle.pointCx * (triangle.pointAy - triangle.pointBy));
    return 0.5 * absValue(sum);
}

void sortTrianglesAscendingByArea(Triangle* triangles, int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            double currentArea = triangleArea(triangles[j]);
            double nextArea = triangleArea(triangles[j + 1]);
            if (nextArea < currentArea) {
                swapTriangles(triangles[j], triangles[j + 1]);
            }
        }
    }
}

void printTriangle(const Triangle& triangle) {
    cout << "A(" << triangle.pointAx << ", " << triangle.pointAy << ") ";
    cout << "B(" << triangle.pointBx << ", " << triangle.pointBy << ") ";
    cout << "C(" << triangle.pointCx << ", " << triangle.pointCy << ") ";
    cout << "Area: " << triangleArea(triangle) << "\n";
}


int main() {

    int N;
    cout << "Enter a number of triangles: \n";
    cin >> N;
    Triangle* triangles = new Triangle[N];
    
    for (int i = 0; i < N; i++) {
        cout << "\nTriangle " << i + 1 << ":\n";
        readTriangle(triangles[i]);
    }

    sortTrianglesAscendingByArea(triangles, N);
    cout << "Triangles sorted by area in ascending order: \n";
    for (int i = 0; i < N; i++) {
        printTriangle(triangles[i]);
    }

    delete[] triangles;
}