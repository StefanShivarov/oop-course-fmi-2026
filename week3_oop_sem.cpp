#include <iostream>
#include <print>
#include <cstring>

namespace utils {

    char* copyDynamicString(const char* src) {
        if (!src) {
            char* result = new char[1];
            result[0] = '\0';
            return result;
        }

        size_t len = strlen(src) + 1;
        char* result = new char[len];
        strcpy_s(result, len, src);
        return result;
    }
}

class Person {
private:
    char* name=nullptr;
    int age=0;
public:
    Person() : Person("Unknown", 0) {

    }

    Person(const char* name, int age) : age(age) {
        this->name = utils::copyDynamicString(name);
    }

    ~Person() {
        delete[] name;
        name = nullptr;
    }

    const char* getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    void setName(const char* newName) {
        delete[] name;
        name = utils::copyDynamicString(newName);
    }

    void setAge(int newAge) {
        if (newAge < 16) {
            return;
        }
        age = newAge;
    }
};

class Parcel {
private:
    Person* sender = nullptr;            //aggregation 
    Person* receiver = nullptr;         //aggregation
    double price = 0.0;
    char* status=nullptr;

public:
    
    Parcel() : sender(nullptr), receiver(nullptr), price(0.0) {
        status = utils::copyDynamicString("Unknown");
    }

    Parcel(Person* sender, Person* receiver, double price, const char* status)
        : sender(sender), receiver(receiver), price(price) {
        this->status = utils::copyDynamicString(status);
    }

    ~Parcel() {
        delete[] status;
    }

    const Person* getSender() const {
        return sender;
    }

    const Person* getReceiver() const {
        return receiver;
    }

    double getPrice() const {
        return price;
    }

    const char* getStatus() const {
        return status;
    }

    void setPrice(double price) {
        this->price = price;
    }

    void setStatus(const char* newStatus) {
        delete[] status;
        status = utils::copyDynamicString(newStatus);
    }

    void changeReceiver(Person* other) {
        receiver = other;
    }

    void print() const {
        std::println("Sender: {}, Receiver: {}, Price: {}, Status: {}",
            sender ? sender->getName() : "Unknown",
            receiver ? receiver->getName() : "Unknown",
            price,
            status);
    }
};

int main() {
    Person p1("Ivan", 25);
    Person p2("Maria", 30);
    Person p3("Georgi", 40);

    Parcel parcel(&p1, &p2, 12.5, "Preparing");
    parcel.print();

    std::println("--- Changing receiver ---");
    parcel.changeReceiver(&p3);
    parcel.print();

    std::println("--- Updating price ---");
    parcel.setPrice(18.75);
    parcel.print();

    std::println("--- Updating status ---");
    parcel.setStatus("Delivered");
    parcel.print();
}
