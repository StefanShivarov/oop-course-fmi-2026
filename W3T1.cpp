#include <iostream>

void Strcpy(char* destination, const char* source)
{
    while (*source)
    {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
}

class Person
{
private:
    char* name = nullptr;
    int age = 0;
    char* address = nullptr;

public:
    Person(const char* name, int age, const char* address)
    {
        this->name = new char[strlen(name) + 1];
        Strcpy(this->name, name);

        this->address = new char[strlen(address) + 1];
        Strcpy(this->address, address);

        this->age = age;
    }

    void PrintInformation() const
    {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << std::endl;
        std::cout << "Address: " << address << std::endl;
    }

    const char* returnName() const
    {
        return name;
    }

    const char* returnAddress() const
    {
        return address;
    }

    ~Person()
    {
        delete[] name;
		age = 0;
        delete[] address;
    }
};

class Packet
{
private:
    char* description;
    double price;
    int status = -1;
    const Person* sender;
    const Person* receiver;

public:

    Packet(const char* description, double price,
        const Person& sender,
        const Person& receiver)
    {
        this->description = new char[strlen(description) + 1];
        Strcpy(this->description, description);

        this->price = price;
        this->sender = &sender;
        this->receiver = &receiver;
    }

    void changeReceiver(const Person& person)
    {
        receiver = &person;
    }
    void changeDescription(const char* description) {
        delete[] this->description;
        this->description = new char[strlen(description) + 1];
        Strcpy(this->description, description);

    }

    void changePrice(double price)
    {
        this->price = price;
    }

    void PrintInformation() const
    {
        std::cout << "Description: " << description << std::endl;
        std::cout << "Address: " << receiver->returnAddress() << std::endl;
        std::cout << "Price for delivery: " << price << std::endl;
        std::cout << "Sender: " << sender->returnName() << std::endl;
        std::cout << "Receiver: " << receiver->returnName() << std::endl;
    }

    ~Packet()
    {
        price = 0;
        delete[] description;
		status = -1;
		Person* sender = nullptr;
		Person* receiver = nullptr;
    }
};

int main()
{
    Person p1("Slavi", 15, "Sofia");
	Person p2("Gosho", 20, "Plovdiv");
	Person p3("Pesho", 25, "Varna");

    Packet p("Laptop", 15.6, p1, p2);
    p.PrintInformation();
    std::cout << "---------------" << std::endl;
	p.changeReceiver(p3);
	p.changePrice(20.5);
    p.changeDescription("Laptop Asus A64B");
    p.PrintInformation();
    

    //8.30
   
}