#include <iostream>
using namespace std;

enum class Status {
    Processing, Shipping, Delivered
};
enum class Gender {
    Male, Female
};
class Person {
    char* name;
    int age;
    Gender gender;
    public:
    Person(const char* name, const int age, const Gender gender) : age(age), gender(gender) {
        this -> name = new char[strlen(name) + 1];
        strcpy(this -> name, name);
    }
    ~Person() {
        delete[] name;
        println("Person closed");
    }
    void print() const {
        char sex[7];
        if (gender == Gender::Male) {
            strcpy(sex, "Male");
        }
        else if (gender == Gender::Female) {
            strcpy(sex, "Female");
        }
        println("{}, {} years old, {}", name, age, sex);
    }
};
class Package {
    char* description;
    double deliveryPrice;
    Status status;
    Person sender;
    Person receiver;
public:
    Package(const char* description, const double deliveryPrice, const Status status, const Person& sender, const Person& receiver) : deliveryPrice(deliveryPrice), status(status), sender(sender), receiver(receiver) {
        this -> description = new char[strlen(description) + 1];
        strcpy(this -> description, description);
    }
    ~Package() {
        delete[] description;
        println("Package closed");
    }
    void reroute(const Person& anotherReceiver) {
        receiver = anotherReceiver;
    }
    void changeDescription(const char* newDescription) {
        strcpy(description, newDescription);
    }
    void changeRate(const double newRate) {
        deliveryPrice = newRate;
    }
    void updateStatus() {
        if (status == Status::Processing) {
            status = Status::Shipping;
        }
        else if (status == Status::Shipping) {
            status = Status::Delivered;
        }
    }
    void print() const{
        char stage[11];
        if (status == Status::Processing) {
            strcpy(stage, "Processing");
        }
        else if (status == Status::Shipping) {
            strcpy(stage, "Shipping");
        }
        else if (status == Status::Delivered) {
            strcpy(stage, "Delivered");
        }
        println("{}, {}€, {}", description, deliveryPrice, stage);
        std::print("From: ");
        sender.print();
        std::print("To: ");
        receiver.print();
    }
};
int main() {
    const Person p1 = Person("Ivan", 34, Gender::Male);
    const Person p2 = Person("Irina", 26, Gender::Female);
    const Person p3 = Person("Elena", 18, Gender::Female);
    Package package = Package("Audi RS7 Performance", 120000, Status::Processing, p1, p2);
    package.print();
    println();
    package.reroute(p3);
    package.changeDescription("BMW M5 G90");
    package.changeRate(110000);
    package.updateStatus();
    package.print();
}