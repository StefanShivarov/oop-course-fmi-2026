#include <iostream>
#include <string>
#include <print>
using namespace std;

enum class Status
{
    NotSent,
    InTransit,
    Arrived
};
string statusToString(Status s)
{
    switch (s)
    {
    case Status::NotSent:
        return "Not sent";
    case Status::InTransit:
        return "In transit";
    case Status::Arrived:
        return "Arrived";
    default:
        return "Unknown status";
    }
}
class Person 
{
private:
    string address;
    string name;
    int age;
public:
    void celebrateBirthday()
    {
        ++age;
    }
    void setAddress(string newAddress)
    {
        address = newAddress;
    }
    int getAge() const
    {
        return age;
    }
    string getAddress() const
    {
        return address;
    }
    string getName() const
    {
        return name;
    }
    void printPersonInfo() const
    {
        println("{}, age - {}, address - \"{}\"", name, age, address);
    }
    Person()
    {
        name = "n/a";
        age = 0;
        address = "n/a";
    }
    Person(string personInfo)
    {
        //format <name>,<age>,<address>
        int i = 0;
        while (personInfo[i] != ',')
        {
            name += personInfo[i];
            i++;
        }
        i++; // moving after comma
        age = 0;
        while (personInfo[i] != ',')
        {
            age *= 10;
            age += personInfo[i] - '0';
            i++;
        }
        i++;
        while (personInfo[i] != '\0')
        {
            address += personInfo[i];
            i++;
        }
    }
    ~Person() = default;
};

class Package
{
private:
    string description;
    double price;
    Status status;
    Person sender;
    Person receiver;
public:
    double getPrice() const
    {
        return price;
    }
    string getDescription() const
    {
        return description;
    }
    Status getStatus() const
    {
        return status;
    }
    void sendPackage()
    {
        status = Status::InTransit;
        println("Package successfully sent!");
    }
    void deliverPackage()
    {
        if (status == Status::InTransit)
        {
            status = Status::Arrived;
            println("Package successfully delivered!");
        }
        else
        {
            println("Package can't be delivered, because it hasn't been sent yet!");
        }
    }
    void ChangeReceiver(Person newReceiver)
    {
        receiver = newReceiver;
    }
    void changeDescription(string newDescription)
    {
        description = newDescription;
    }
    void changePrice(double newPrice)
    {
        price = newPrice;
    }
    void printPackageInfo() const
    {
        print("Sender: ");
        sender.printPersonInfo();
        print("Receiver: ");
        receiver.printPersonInfo();
        println("Description: {}", description);
        println("Price: {}", price);
        println("Status: {}", statusToString(status));

    }
    Package() = default;
    Package(string dscr,double prc,const Person& sndr,const Person& rcvr)
    {
        sender = sndr;
        receiver = rcvr;
        status = Status::NotSent;
        description = dscr;
        price = prc;
    }
    ~Package() = default;
};
int main()
{
    println("How many people will you enter?");
    int numPersons;
    cin >> numPersons;
    cin.ignore();
    Person* persons = new Person[numPersons];
    println("Format - <name>,<age>,<address>");
    println("Enter {} people:",numPersons);
    for (int i = 0;i < numPersons;i++)
    {
        string tempInfo;
        getline(cin, tempInfo);
        Person tempPerson(tempInfo);
        persons[i] = tempPerson;
    }
    println("\n\n-----List of people-----");
    for (int i = 0;i < numPersons;i++)
    {
        print("Person {}- ", i);
        persons[i].printPersonInfo();
    }

    println("\n\nHow many packages will you send?");
    int numPackages;
    cin >> numPackages;
    cin.ignore();
    Package* packages = new Package[numPackages];
    for (int i = 0;i < numPackages;i++)
    {
        string description;
        double price;
        int senderIndex;
        int receiverIndex;
        println("Package {}:", i);
        print("Description: ");
        getline(cin, description);
        print("Price of service: ");
        cin >> price;
        print("Number of sender: ");
        cin >> senderIndex;
        print("Number of receiver: ");
        cin >> receiverIndex;
        cin.ignore();
        packages[i] = Package(description, price, persons[senderIndex], persons[receiverIndex]);
    }
    println("\n\n-----List of packages-----");
    for (int i = 0;i < numPackages;i++)
    {
        println("Package {}:", i);
        packages[i].printPackageInfo();
        println("------------------------------");
    }
    println("\n\n(enter 0 for no and 1 for yes)");
    for (int i = 0;i < numPackages;i++)
    {
        bool change = 0;
        print("Change package {}'s price?: ", i);
        cin >> change;
        if (change)
        {
            double price;
            print("Enter new price: ");
            cin >> price;
            packages[i].changePrice(price);
        }
    }
    for (int i = 0;i < numPackages;i++)
    {
        bool change = 0;
        print("Change package {}'s receiver?: ", i);
        cin >> change;
        if (change)
        {
            int index;
            print("Enter new receiver's number: ");
            cin >> index;
            packages[i].ChangeReceiver(persons[index]);
        }
    }
    for (int i = 0;i < numPackages;i++)
    {
        bool change = 0;
        print("Change package {}'s description?: ", i);
        cin >> change;
        cin.ignore();
        if (change)
        {
            string desc;
            print("Enter new description: ");
            getline(cin, desc);
            packages[i].changeDescription(desc);
        }
    }
    println("\n\n-----Sending out packages-----");
    for (int i = 0;i < numPackages;i++)
    {
        bool send = 0;
        print("Send package {}?: ", i);
        cin >> send;
        if (send)
        {
            packages[i].sendPackage();
        }
    }
    println("\n\n-----Delivering packages-----");
    for (int i = 0;i < numPackages;i++)
    {
        bool deliver = 0;
        print("Deliver package {}?: ", i);
        cin >> deliver;
        if (deliver)
        {
            packages[i].deliverPackage();
        }
    }
    println("\n\n-----List of packages-----");
    for (int i = 0;i < numPackages;i++)
    {
        println("Package {}:", i);
        packages[i].printPackageInfo();
        println("------------------------------");
    }
    delete[] persons;
    delete[] packages;
}
