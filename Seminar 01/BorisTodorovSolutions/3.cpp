#include <iostream>
#include <print>
using namespace std;
struct point
{
    int x, y;
};
class Triangle
{
private:
    point A, B, C;
    double area;
public:
    Triangle()
    {
        A.x = 0;A.y = 0;
        B.x = 0;B.y = 0;
        C.x = 0;C.y = 0;
        area = 0;
    }
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        A.x = x1;A.y = y1;
        B.x = x2;B.y = y2;  
        C.x = x3;C.y = y3;
        area = (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)) / 2.0;
        if (area < 0)
            area *= -1;
    }
    void printTriangle()
    {
        println("A:({},{}), B:({},{}), C:({},{}), area:{}", A.x, A.y, B.x, B.y, C.x, C.y, area);
    }
    double getArea()
    {
        return area;
    }
};
void swapTriangles (Triangle& a,Triangle& b)
{
    Triangle temp = a;
    a = b;
    b = temp;
}
void printTrianglesByArea(int n,Triangle* triangles)
{
    Triangle* sortedTriangles = new Triangle[n];
    for (int i = 0;i < n;i++)
    {
        sortedTriangles[i] = triangles[i];
    }
    bool swapped;
    for (int i = 0;i < n - 1;i++)
    {
        swapped = false;
        for (int j = 0;j < n - i - 1;j++)
        {
            if (sortedTriangles[j].getArea() < sortedTriangles[j + 1].getArea())
            {
                swapTriangles(sortedTriangles[j], sortedTriangles[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }

    for (int i = 0;i < n;i++)
    {
        sortedTriangles[i].printTriangle();
    }
    delete[] sortedTriangles;
}
int main()
{
    int n;
    cin >> n;
    Triangle* triangles = new Triangle[n];

    for (int i = 0;i < n;i++)
    {
        int x1, x2, x3, y1, y2, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        triangles[i] = Triangle(x1, y1, x2, y2, x3, y3);
    }

    printTrianglesByArea(n, triangles);
    delete[] triangles;
}

