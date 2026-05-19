#include <iostream>
#include <memory>
#include "Point.h"
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "PolymorphicContainerUnique.hpp"
#include "PolymorphicContainerShared.hpp"
#include "PolymorphicContainerSharedShallow.hpp"

int main() {
    try {
        std::cout << "---(Task 1) ---\n";

        Circle circle("MyCircle", Point(0, 0), 5);
        Rectangle rect("MyRect", Point(0, 0), Point(4, 3));
        Triangle triangle("MyTriangle", Point(0, 0), Point(4, 0), Point(0, 3));

        circle.printInfo();
        rect.printInfo();
        triangle.printInfo();

        Point inside(1, 1);
        Point outside(10, 10);

        std::cout << "Is (1,1) inside Circle ? " << (circle.isPointInside(inside) ? "Yes" : "No") << "\n";
        std::cout << "IS (10,10) inside Circle? " << (circle.isPointInside(outside) ? "Yes" : "No") << "\n";
        std::cout << "Is (1,1) inside Triangle ? " << (triangle.isPointInside(inside) ? "Yes" : "No") << "\n";

        std::cout << "\n---  1: Unique Deep Copy ---\n";
        {
            PolymoprhicContainerUnique<Shape> container1;
            container1.add(circle);
            container1.add(rect);

            std::cout << "Original Container 1:\n";
            container1.print();

            PolymoprhicContainerUnique<Shape> container2 = container1;
            std::cout << "Copied Container 2 (Deep Copy):\n";
            container2.print();

            std::cout << "First shape is: " << container1[0].getType() << "\n";
        }

        std::cout << "\n---  2: Shared Deep Copy ---\n";
        {
            PolymoprhicContainerShared<Shape> deepSharedContainer;
            deepSharedContainer.add(rect);
            deepSharedContainer.add(triangle);

            std::cout << "Deep Shared Container:\n";
            deepSharedContainer.print();

            PolymoprhicContainerShared<Shape> copyContainer = deepSharedContainer;
        }

        std::cout << "\n---  3: Shared Shallow Copy ---\n";
        {
            PolymoprhicContainerSharedShallow<Shape> shallowContainer1;

            auto sharedCircle = std::make_shared<Circle>("SharedCircle", Point(0, 0), 10);

            shallowContainer1.add(sharedCircle);

            PolymoprhicContainerSharedShallow<Shape> shallowContainer2 = shallowContainer1;

            std::cout << "before (Shallow 2):\n";
            shallowContainer2.print();

            std::cout << "successfully shared Shallow Copy!\n";
        }

        std::cout << "\n--- exceptions ---\n";
        std::cout << "trying to make an invalid tri...\n";
        Triangle invalidTriangle("BadTriangle", Point(0, 0), Point(1, 1), Point(2, 2));

    }
    catch (const std::invalid_argument& e) {
        std::cout << "expected " << e.what() << "\n";
    }
    catch (const std::out_of_range& e) {
        std::cout << "index " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "error: " << e.what() << "\n";
    }

    return 0;
}