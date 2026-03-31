#include <iostream>
#include <cstring>

using std::cout;
using std::endl;
using std::ostream;

class Person {
private:
    char* name = nullptr;
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

class Shipment {
private:
    char* description = nullptr;
    double deliveryPrice = 0.0;
    const Person* sender = nullptr;
    const Person* receiver = nullptr;

public:
    Shipment(const char* description, double deliveryPrice, const Person* sender) {
        setDescription(description);
        setDeliveryPrice(deliveryPrice);
        setSender(sender);
    }

    Shipment(const char* description, double deliveryPrice, const Person* sender, const Person* receiver)
        : Shipment(description, deliveryPrice, sender) {
        setReceiver(receiver);
    }

    ~Shipment() {
        delete[] description;
        description = nullptr;
        deliveryPrice = 0.0;
        sender = nullptr;
        receiver = nullptr;
    }

    const char* getDescription() const {
        return description;
    }

    bool setDescription(const char* desc) {
        if (!desc) {
            return false;
        }

        delete[] description;
        description = new char[strlen(desc) + 1];
        strcpy(description, desc);
        return true;
    }

    double getDeliveryPrice() const {
        return deliveryPrice;
    }

    bool setDeliveryPrice(double deliveryPrice) {
        if (deliveryPrice < 0) {
            return false;
        }
        this->deliveryPrice = deliveryPrice;
        return true;
    }

    const Person* getSender() const {
        return sender;
    }

    bool setSender(const Person* sender) {
        if (!sender || sender == receiver) {
            return false;
        }
        this->sender = sender;
    }

    const Person* getReceiver() const {
        return receiver;
    }

    bool setReceiver(const Person* receiver) {
        if (!receiver || receiver == sender) {
            return false;
        }
        this->receiver = receiver;
        return true;
    }

};

void printShipment(const Shipment& shipment, ostream& os = cout) {
    os << "Description: " << shipment.getDescription() << '\n';
    os << "Price: " << shipment.getDeliveryPrice() << '\n';
    if (shipment.getSender()) {
        os << "Sender: " << shipment.getSender()->getName() << '\n';
    }
    if (shipment.getReceiver()) {
        os << "Receiver: " << shipment.getReceiver()->getName() << '\n';
    }
}

int main() {
    Person stefo("Stefo", 35);
    Person serhan("Serhan", 28);
    Shipment shipment("Burkani s lyutenitsa", 12.50, &stefo, &serhan);
    printShipment(shipment);
}
