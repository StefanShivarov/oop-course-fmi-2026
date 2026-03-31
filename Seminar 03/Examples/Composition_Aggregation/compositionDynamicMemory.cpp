#include <iostream>

using std::cout;
using std::endl;

class Heart {
private:
    int bpm;

public:
    Heart(int bpm = 70) : bpm(bpm) {
        cout << "Heart(" << bpm << ")" << endl;
    }

    void print() const {
        cout << "Heart bpm: " << bpm << '\n';
    }

    ~Heart() {
        cout << "~Heart()" << endl;
    }
};

// This is also composition!
class Human {
private:
    int age;
    Heart* heart = nullptr; // composition: а Human "owns" a heart and is responsible for its lifecycle
    // ...

public:
    Human(int age, int bpm) : age(age) {
        this->heart = new Heart(bpm);
        cout << "Human()" << endl;
    }

    void print() const {
        cout << "Human age: " << age << '\n';
        heart->print();
    }

    ~Human() {
        delete heart; // ~Heart()
        cout << "~Human()" << endl;
    }
};

int main() {
    Human h(25, 72); //~Heart(72) ~Human()
    h.print();
} // ~Heart() ~Human()
