#include <iostream>
#pragma warning (disable:4996)
const int MAX_SIZE_OF_NAME = 50;


class Person {
private:
	char* name = nullptr;
	int age;
public:
	Person(const char* name, int age) : age(age) {
		if (name == nullptr)
		{
			std::cout << "Invalid name \n";
			return;
		}
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}

	~Person() {
		delete[] name;
	}
	char* getName() const {
		return name;
	}
};

class Package {
private:
	char* description = nullptr;
	double price;
	Person* sender;
	Person* receiver;
public:
	Package(const char* desc, Person* s, Person* r, double price) :  sender(s), receiver(r), price(price) {
		description = new char[strlen(desc) + 1];
		strcpy(description, desc);
	}

	~Package() {
		delete[] description;
	}
	bool isValid() const {
		if ((description == nullptr) || (receiver == nullptr) || (sender == nullptr) || (price < 0))
		{
			return false;
		}
		return true;
	}
	void changeReceiver(Person* newReceiver) {
		if (newReceiver == nullptr)
		{
			std::cout << "The package was not redirected \n";
			return;
		}
		receiver = newReceiver;
		std::cout << "The package was redirected successfully \n";
	}
	void changeDescription(const char* newDesc) {
		if (newDesc == nullptr)
		{
			std::cout << "The description was not changed \n";
			return;
		}
		delete[] description;
		description = new char[strlen(newDesc) + 1];
		strcpy(description, newDesc);
		std::cout << "The description was changed successfully \n";
	}
	void setPrice(double newPrice) {
		if (newPrice < 0)
		{
			std::cout << "Invalid price \n";
			return;
		}
		price = newPrice;
		std::cout << "The price was changed successfully \n";
	}
	
	void printInfo()const {
		if (!isValid())
		{
			std::cout << "There is a problem with the information \n";
			return;
		}
		std::cout << "Description: " << description <<
			".It is sent by " << sender->getName() << " ,and recieved by " << receiver->getName()
			<< " ,who has to pay a total of: " << price << " euro. \n";
 	}
	
};

int main()
{
	Person p1("Ivan", 25);
	Person p2("Maria", 22);
	Person p3("Petar", 30);

	Package pkg("Telefon", &p1, &p2, 20.50);
	pkg.printInfo();

	pkg.changeReceiver(&p3);      
	pkg.changeDescription("Laptop"); 
	pkg.setPrice(25.00);           

	std::cout << "\nSled promenite:\n";
	pkg.printInfo();

	return 0;
}
