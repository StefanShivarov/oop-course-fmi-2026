#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::ostream;

int myStrlen(const char* str) {
    if (str != nullptr) {
        int length = 0;
        while (str[length] != '\0') {
            length++;
        }
        return length;
    }
    return 0;
}

void myStrcpy(char* destination, const char* source) {
    if (source != nullptr && destination!= nullptr) {
        int i = 0;
        while (source[i] != '\0') {
            destination[i] = source[i];
            i++;
        }
        destination[i] = '\0';
    }
}

class Person {
    private:
        char* name = nullptr;
        int age;
    public:
        Person() : Person("N/A", 0) {
        }
        Person (const char* name, int age) {
            setName(name);
            setAge(age);
        }
        ~Person () {
            delete[] name;
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
            if (name == nullptr) {
                return;
            }
            delete[] this->name;
            this->name = new char[myStrlen(name) + 1];
            myStrcpy(this->name, name);
        }
        void setAge(const int age) {
            if (age <= 0 || age >= 100) {
                return;
            }
            this->age = age;
        }
};

class Shipment {
    private:
        char* description = nullptr;
        double price = 0.0;
        char* status = nullptr;
        const Person* sender = nullptr;
        const Person* receiver = nullptr;
    public:
        Shipment (const char* description, double price, const char* status, const Person* sender) {
            setDescription(description);
            setPrice(price);
            setStatus(status);
            setSender(sender);
        }
        Shipment (const char* description, double price, const char* status, const Person* sender, const Person* receiver) : Shipment(description, price, status, sender) {
            setReceiver(receiver);
        }
        ~Shipment () {
            delete[] description;
            description = nullptr;
            delete[] status;
            status = nullptr;
            price = 0.0;
            sender = nullptr;
            receiver = nullptr;
        }
        const char* getDescription() const {
            return description;
        }
        double getPrice() const {
            return price;
        }
        const char* getStatus() const {
            return status;
        }
        const Person* getSender() const {
            return sender;
        }
        const Person* getReceiver() const {
            return receiver;
        }

        bool setDescription(const char* description) {
            if (description == nullptr) {
                return false;
            }
            delete[] this->description;
            this->description = new char[myStrlen(description) + 1];
            myStrcpy(this->description, description);
            return true;
        }
        bool setPrice(double price) {
            if (price <= 0) {
                return false;
            }
            this->price = price;
            return true;
        }
        bool setStatus(const char* status) {
            if (status == nullptr) {
                return false;
            }
            delete[] this->status;
            this->status = new char[myStrlen(status) + 1];
            myStrcpy(this->status, status);
            return true;
        }
        bool setSender(const Person* sender) {
            if (sender == nullptr || sender == receiver) {
                return false;
            }
            this->sender = sender;
            return true;
        }
        bool setReceiver(const Person* receiver) {
            if (receiver == nullptr || receiver == sender) {
                return false;
            }
            this->receiver = receiver;
            return true;
        }
        void printShipment(ostream& os = cout) const {
            os << "Description: " << getDescription() << endl;
            os << "Price: " << getPrice() << endl;
            os << "Status: " << getStatus() << endl;
            if (getSender() != nullptr) {
                os << "Sender: " << getSender()->getName() << ", " << getSender()->getAge() << endl;
            }
            if (getReceiver() != nullptr) {
                os << "Receiver: " << getReceiver()->getName() << ", " << getReceiver()->getAge() << endl;
            }
        }
};

int main() {
    Person sender("person1", 19);
    Person receiver("person2", 19);
    Shipment shipment("Canned pineapples", 3.99, "In transit", &sender, &receiver);
    shipment.printShipment();
    return 0;
}
