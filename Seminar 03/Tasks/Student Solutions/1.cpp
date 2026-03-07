#include <iostream>
#include <cstring>

class Person
{
private:
    char *name = nullptr;
    unsigned int age = 0;

public:
    void printPerson() const
    {
        if (!name)
        {
            return;
        }
        std::cout << "\nName: " << name;
        std::cout << "\nAge:" << age;
    }
    Person()
    {
        name = new char[1];
        name[0] = '\0';
    }
    ~Person()
    {
        delete[] name;
    }
    Person(const char *name, const unsigned int age) : age(age)
    {
        if (!name)
        {
            this->name = new char[1];
            this->name[0] = '\0';
            return;
        }
        this->name = new char[std::strlen(name) + 1];
        std::strcpy(this->name, name);
    }
    const char *getName() const
    {
        return name;
    }
    unsigned int getAge() const
    {
        return age;
    }
    void setAge(const unsigned int age)
    {
        this->age = age;
    }
    void setName(const char *name)
    {
        delete[] this->name;
        if (!name)
        {
            this->name = nullptr;
            return;
        }
        this->name = new char[std::strlen(name) + 1];
        std::strcpy(this->name, name);
    }
};
enum class Status
{
    Waiting,
    Sent,
    Delivered
};
void printStatus(const Status s)
{
    switch (s)
    {
    case Status::Delivered:
        std::cout << "\nDelivered";
        break;
    case Status::Sent:
        std::cout << "\nSent";
        break;
    default:
        std::cout << "\nWaiting";
        break;
    }
}
class Delivery
{
private:
    char *description = nullptr;
    double price = 0.0;
    Status status = Status::Waiting;
    const Person *sender = nullptr;
    const Person *receiver = nullptr;

public:
    Delivery()
    {
    }
    Delivery(const char *description, double price, Status status, Person *sender, Person *receiver)
    {
        if (!description)
        {
            this->description = new char[1];
            this->description[0] = '\0';
        }
        else
        {
            this->description = new char[std::strlen(description) + 1];
            std::strcpy(this->description, description);
        }
        this->price = price;
        this->status = status;
        this->sender = sender;
        this->receiver = receiver;
    }
    void printDelivery() const
    {
        std::cout << "\nDescription: ";
        if (!description)
        {
            std::cout << "None";
        }
        else
        {
            std::cout << description;
        }
        std::cout << "\nPrice: "
                  << this->price;
        printStatus(this->status);
        std::cout << "\nSender: ";
        if (!this->sender)
        {
            std::cout << "N/A";
        }
        else
        {
            this->sender->printPerson();
        }
        std::cout << "\nReceiver: ";
        if (!this->receiver)
        {
            std::cout << "N/A";
        }
        else
        {
            this->receiver->printPerson();
        }
    }
    void changeReceiver(Person *newReceiver)
    {
        this->receiver = newReceiver;
    }
    void changeSender(Person *newSender)
    {
        this->sender = newSender;
    }
    void changeDescription(const char *ch)
    {
        if (!ch)
        {
            return;
        }
        delete[] description;
        description = new char[strlen(ch) + 1];
        std::strcpy(description, ch);
    }
    void changePrice(double price)
    {
        this->price = price;
    }
    ~Delivery()
    {
        delete[] description;
    }
    double getPrice() const
    {
        return price;
    }
    const char *getDescription() const
    {
        return description;
    }
    const Person *getSender() const
    {
        return sender;
    }
    const Person *getReceiver() const
    {
        return receiver;
    }
    Status getStatus() const
    {
        return status;
    }
};

int main()
{
    Person p("Stefan", 23);
    Person p1("Serhan", 23);
    Delivery d("Empty", 1, Status::Delivered, &p, &p);
    d.changeDescription("W");
    d.changeReceiver(&p1);
    d.changePrice(3456);
    d.printDelivery();
}