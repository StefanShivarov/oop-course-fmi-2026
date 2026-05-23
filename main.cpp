
#include <iostream>
#include <vector>
#include <memory>
#include "Circle.h"
#include "Reactngle.h"
#include "Triangle.h"

void print(const Shape& s)
{
    std::cout << "area: " << s.area() << " perimeter: " << s.perimeter() << '\n';
}

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(0.0, 0.0, 4.0));
    shapes.push_back(std::make_unique<Rectangle>(0.0, 0.0, 5.0, 3.0));
    shapes.push_back(std::make_unique<Triangle>(0.0, 0.0, 4.0, 0.0, 0.0, 3.0));

    for (const auto& s : shapes)
    {
        print(*s);
    }

    std::cout << "Is (1,1) inside the circle? " << shapes[0]->isIn(1, 1) << '\n';
    std::cout << "Is (10,10) inside the circle? " << shapes[0]->isIn(10, 10) << '\n';
}

