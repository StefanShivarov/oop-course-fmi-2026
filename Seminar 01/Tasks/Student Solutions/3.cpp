#include <iostream>

const int MAX_TRIANGLES = 10;

struct Point
{
    int x;
    int y;
};

struct Triangle
{
    Point a;
    Point b;
    Point c;
};

void swap(Triangle &t1, Triangle &t2)
{
    Triangle temp = t1;
    t1 = t2;
    t2 = temp;
}

double findArea(const Triangle& t)
{
    return (1.0 / 2) * (std::abs(double(t.b.x - t.a.x) * (t.c.y - t.a.y) - double(t.c.x - t.a.x) * (t.b.y - t.a.y)));
}

bool isValidTriangle(const Triangle& t)
{
    double eps = 0.000001;
     if (findArea(t) < eps)
    {
        std::cout << "\nInvalid\n";
        return false;
    }
    return true;
}


void sortByArea(Triangle t[MAX_TRIANGLES], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (findArea(t[j]) > findArea(t[j + 1]))
            {
                swap(t[j], t[j + 1]);
            }
        }
    }
}

void printTriangle(const Triangle& t)
{
    std::cout << "\n";
    std::cout << "(" << t.a.x << "," << t.a.y << "), ";
    std::cout << "(" << t.b.x << "," << t.b.y << "), ";
    std::cout << "(" << t.c.x << "," << t.c.y << ")\n";
    std::cout << "Area: " << findArea(t);
}

void printAllTriangles(const Triangle t[MAX_TRIANGLES], int n)
{
    for (int i = 0; i < n; i++)
    {
        printTriangle(t[i]);
    }
}

int main()
{
    int n;
    std::cin >> n;
    Triangle t[MAX_TRIANGLES];
    int x1, y1, x2, y2, x3, y3;
    for (int i = 0; i < n; i++)
    {
        do
        {
            std::cout << "Enter coordinates of the first point\n";
            std::cin >> x1;
            std::cin >> y1;
            std::cout << "Enter coordinates of the second point\n";
            std::cin >> x2;
            std::cin >> y2;
            std::cout << "Enter coordinates of the third point\n";
            std::cin >> x3;
            std::cin >> y3;
            t[i] = {{x1, y1}, {x2, y2}, {x3, y3}};
        } while (!isValidTriangle(t[i]));
    }
    sortByArea(t, n);
    printAllTriangles(t, n);
}