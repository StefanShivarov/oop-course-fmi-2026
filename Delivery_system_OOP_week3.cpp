#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<print>
#include<cstring>

using std::print;
using std::println;

enum class Status
{
    WAITING,
    INPROGRESS,
    DELIVERED,
    OTHER
};
class Person
{
    char name[50];
    int age;
    char town[20];

public:
    Person() = default;

    Person(const char* name, int age, const char* town) :age(age)
    {
        strcpy(this->name, name);
        strcpy(this->town, town);
    }

    const char* getName()const
    {
        return name;
    }

    int getAge()const
    {
        return age;
    }

    const char* getTown()const
    {
        return town;
    }

    void printPerson()const
    {
        println("Name:{},Age:{},Town:{}", name, age, town);
    }
};

class Delivery
{
    char description[50];
    double price;
    Status status;
    Person* sender;
    Person* taker;

    Status convertToStatus(const char* status)const
    {
        if (strcmp(status, "In progress") == 0)
        {
            return Status::INPROGRESS;
        }
        else if (strcmp(status, "Waiting") == 0)
        {
            return Status::WAITING;
        }
        else if (strcmp(status, "Delivered") == 0)
        {
            return Status::DELIVERED;
        }
        else
        {
            return Status::OTHER;
        }
    }

    const char* convertToString(const Status& status)const
    {
        switch (status)
        {
        case Status::WAITING:return"Waiting";
        case Status::INPROGRESS:return "In progress";
        case Status::DELIVERED:return "Delivered";
        default:return "Other";
        }
    }

public:
    Delivery() = default;
    
    Delivery(const char* description, double price, const char* status, Person* sender,
        Person* taker) :price(price),sender(sender),taker(taker)
    {
        strcpy(this->description, description);
        this->status = convertToStatus(status);
    }

    ~Delivery() = default;

    const char* getDescription() const
    {
        return description;
    }

    double getPrice() const
    {
        return price;
    }

    Status getStatus() const
    {
        return status;
    }

    void setPrice(double price)
    {
        if (price < 0)
        {
            println("Invalid input!");
            return;
        }

        this->price = price;
    }

    void setTaker(Person* newTaker)
    {
        taker = newTaker;
    }

    void setDescription(const char* newDescription)
    {
        strcpy(description, newDescription);
    }


    void printDelivery()const
    {
        println("Description:{},Price:{},Status:{}", description, price,convertToString(status));
        println("Sender:");
        sender->printPerson();
        println("Taker:");
        taker->printPerson();
        println();
    }

};

int main()
{
    Person p1("Ivan", 25, "Sofia");
    Person p2("Maria", 22, "Plovdiv");
    Person p3("Georgi", 30, "Varna");
    Person p4("Katerina", 35, "Gabrovo");
    Person p5("Ema", 25, "Lovech");

    Delivery d1("Phone delivery", 15.50, "Waiting", &p1, &p2);
    Delivery d2("Headphones delivery", 20.50, "In progress", &p1, &p3);
    Delivery d3("Cakes delivery", 30, "Delivered", &p4, &p5);
    
    d1.printDelivery();
    d2.printDelivery();
    d3.printDelivery();

    d2.setDescription("Flowers delivery");
    d1.setPrice(14.20);
    d2.setTaker(&p2);

    println("After the changes:");
    d1.printDelivery();
    d2.printDelivery();
    d3.printDelivery();

    return 0;
}

