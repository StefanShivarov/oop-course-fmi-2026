#include <iostream>
#include <cmath>

using std::cin;
using std::cout;

struct Triangle {
    double a, b, c;

    bool isTriangle() {

        return a > 0 && b > 0 && c > 0 &&
            a + b > c && a + c > b && b + c > a;
    }

    double getArea() {
        double p = (a + b + c) / 2;
        double area = sqrt(p * (p - a) * (p - b) * (p - c));
        return area;
    }
};

void readTriangle(Triangle* triangle, int N) {
    for (int i = 0; i < N; i++)
    {
        cin >> triangle[i].a >> triangle[i].b >> triangle[i].c;
    }
}


void swap(Triangle& a, Triangle& b) {
    Triangle temp = a;
    a = b;
    b = temp;
}

void sortByArea(Triangle* triangle, int N) {
    for (size_t i = 0; i < N - 1; i++)
    {
        for (size_t j = 0; j < N - i -1; j++)
        {
            if (triangle[j].getArea() > triangle[j + 1].getArea()) {
                swap(triangle[j], triangle[j + 1]);
            }
        }
    }
}

void printTriangle(Triangle* triangles, int N) {
    cout << '\n';
    for (int i = 0; i < N; i++)
    {
        if (triangles[i].isTriangle()) {
            cout << triangles[i].a << " " << triangles[i].b << " " << triangles[i].c << '\n';
        }
        else {
            cout << "The triangle doesnt exist" << '\n';
        }
    }
}

int main()
{
    int N;
    cin >> N;

    Triangle* triangles = new Triangle[N];
    readTriangle(triangles, N);

    sortByArea(triangles, N);
    printTriangle(triangles, N);
   
    delete[] triangles;
}

