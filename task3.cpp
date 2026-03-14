#include <iostream>
using namespace std;

struct Point {
    int x;
    int y;
};
struct Triangle {
    Point p1;
    Point p2;
    Point p3;
    double getFace() const {
        double a = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
        double b = sqrt((p2.x - p3.x) * (p2.x - p3.x) + (p2.y - p3.y) * (p2.y - p3.y));
        double c = sqrt((p3.x - p1.x) * (p3.x - p1.x) + (p3.y - p1.y) * (p3.y - p1.y));
        double p = (a + b + c) / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};
void bubbleSort(Triangle* arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].getFace() > arr[j + 1].getFace()) {
                Triangle temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int main() {
    int n;
    cin >> n;
    Triangle* t = new Triangle[n];
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        t[i].p1 = Point{x1, y1};
        t[i].p2 = Point{x2, y2};
        t[i].p3 = Point{x3, y3};
    }
    bubbleSort(t, n);
    for (int i = 0; i < n; i++) {
        cout << "Triangle " << i + 1 << ": " << t[i].getFace() << endl;
    }
    delete[] t;
}