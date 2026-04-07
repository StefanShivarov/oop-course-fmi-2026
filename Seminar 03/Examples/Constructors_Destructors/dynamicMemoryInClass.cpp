#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

class Person {
private:
    char* name = nullptr; // dynamically allocated (external resource)
    int age;

public:
    Person() : Person("N/A", 0) {
    }

    Person(const char* name, int age) : age(0) {
        setName(name);
        setAge(age);
    }

    ~Person() {
        delete[] name;
        // these below are optional
        name = nullptr;
        age = 0;
    }

    const char* getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    void setName(const char* name) {
        if (!name) {
            return;
        }
        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    void setAge(int age) {
        if (age < 0 || age > 120) {
            return;
        }
        this->age = age;
    }
};

int main() {
    Person p1;
    cout << p1.getName() << ' ' << p1.getAge() << endl;

    Person p2("Stefo", 22);
    cout << p2.getName() << ' ' << p2.getAge() << endl;

    // dynamically allocated memory is handled by the constructor and destructor
}
