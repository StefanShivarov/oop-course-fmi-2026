#include <iostream>
using std::cout;

class Point {
private:
    int x = 0;
    int y = 0;

public:
    Point& setX(int x) {
        this->x = x;
        return *this; // we return a reference to the current object
    }

    Point& setY(int y) {
        this->y = y;
        return *this;
    }

    int getX() const { return x; }
    int getY() const { return y; }
};
    
int main() {
    Point p;
    p.setX(10).setY(20); // this way we can chain the setters like that

    cout << p.getX() << " " << p.getY() << "\n";
}