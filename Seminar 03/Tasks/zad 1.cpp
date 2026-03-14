#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

namespace utils {

    char* copyDynamicString(const char* src) {
        if (!src) {
            char* result = new char[1];
            result[0] = '\0';
            return result;
        }

        char* result = new char[strlen(src) + 1];
        strcpy(result, src);
        return result;
    }
}

class Person 
{

private:
    char* name = nullptr;
    int age = 0;

public:

    Person() : Person("Unknown", 0) {}

    Person(const char* name, int age) : age(age) {
        this->name = utils::copyDynamicString(name);
    }

    ~Person() {
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

    void setName(const char* newName) {
        delete[] name;
        name = utils::copyDynamicString(newName);
    }

    void setAge(int newAge) {
        if (newAge < 0 || newAge > 150) {
            return;
        }
        age = newAge;
    }

    void print() const {
        cout << "Person { name: \"" << name << "\", age: " << age << " }" << endl;
    }
};


enum class PackageStatus {
    Pending, InTransit, Delivered, Redirected
};

const char* statusToStr(PackageStatus s) {

    switch (s) {
    case PackageStatus::Pending: return "Pending";
    case PackageStatus::InTransit: return "In Transit";
    case PackageStatus::Delivered: return "Delivered";
    case PackageStatus::Redirected: return "Redirected";
    default: return "Unknown";
    }
}

class Package {

    private:
        char* description = nullptr;
        double price = 0.0;
        PackageStatus status = PackageStatus::Pending;
        const Person* sender = nullptr;
        const Person* recipient = nullptr; 

    public:
        Package() : Package("No description", 0.0, nullptr, nullptr) {}

        Package(const char* description, double price, const Person* sender, const Person* recipient): sender(sender), recipient(recipient)
        {
            this->description = utils::copyDynamicString(description);
            setPrice(price);
        }

        ~Package() {
            delete[] description;
            description = nullptr;
            price = 0.0;
            sender = nullptr; 
            recipient = nullptr;
        }

    const char* getDescription() const { 
        return description; 
    }
    double getPrice() const {
        return price; 
    }
    PackageStatus getStatus() const {
        return status;
    }
    const Person* getSender() const  {
        return sender; 
    }
    const Person* getRecipient() const {
        return recipient; 
    }

    void setDescription(const char* newDesc) {
        if (!newDesc) {
            return;
        }
        delete[] description;
        description = utils::copyDynamicString(newDesc);
    }

    void setPrice(double newPrice) {
        if (newPrice < 0) {
            return;
        }
        price = newPrice;
    }

    void setStatus(PackageStatus newStatus) {
        status = newStatus;
    }

    void redirectTo(const Person& newRecipient) {
        cout << "Package redirected from \"" << recipient->getName()
            << "\" to \""  << newRecipient.getName() << "\"" << endl;
        recipient = &newRecipient;
        status = PackageStatus::Redirected;
    }

    void print() const {
        cout << "Package {" << endl;
        cout << "  description: \"" << description << "\"" << endl;
        cout << "  price: " << price << " lv." << endl;
        cout << "  status: " << statusToStr(status) << endl;
        cout << "  sender: " << (sender ? sender->getName() : "N/A") << endl;
        cout << "  recipient: " << (recipient ? recipient->getName() : "N/A") << endl;
        cout << "}" << endl;
    }
};

int main() {

    Person petko("Petko",24);
    Person lexi("Lexi", 20);

    cout << "People:" << endl;
    petko.print();
    lexi.print();
    cout << endl;

    Package p1("Laptop", 89.99, &lexi, &petko);
    Package p2("Books", 15.00, &petko, &lexi);

    cout << "Packages after creation: " << endl;
    p1.print();
    p2.print();
    cout << endl;

    p1.setStatus(PackageStatus::InTransit);

    p2.setDescription("Books & Stationery");
    p2.setPrice(22.50);

    p1.redirectTo(lexi);

    cout << "Packages after modifications: " << endl;
    p1.print();
    p2.print();
    cout << endl;

}