

#include <iostream>
#include <print>
#include <format>
#include <cstring>
#pragma warning(disable:4996)

using std::println;
using std::cout;

enum class Status {
	Created, Processing, Shipped, Delivered, Delayed, Returned
};

char* copyStringDyn(const char* src) {
	if (!src) {
		char* result = new char[1];
		result[0] = '\0';
		return result;
	}

	char* result = new char[strlen(src) + 1];
	strcpy(result, src);
	return result;
}

const char* toString(Status s) {
	switch (s) {
	case Status::Created: return "Created";
	case Status::Processing: return "Processing";
	case Status::Shipped: return "Shipped";
	case Status::Delivered: return "Delivered";
	case Status::Delayed: return "Delayed";
	case Status::Returned: return "Returned";
	default:
		return "unknown";
	}
}

class Person {
	char* name = nullptr;
	int age = 0;
public:
	Person(const char* name, int age) : age(age) {
		this->name = copyStringDyn(name);
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
		delete[]name;
		name = copyStringDyn(newName);
	}

	void setAge(int newAge) {
		if (newAge < 0) {
			return;
		}

		age = newAge;
	}

	void printPerson() const {
		println("Name: {}, age: {}", name, age);
	}
};

class Package {
	char* description = nullptr;
	double price = 0.00;
	Status status;
	const Person* sender;
	const Person* receiver;
public:
	Package(const char* description, double price, Status status, const Person& sender, const Person& receiver)
		: price(price), status(status), sender(&sender), receiver(&receiver) {

		this->description = copyStringDyn(description);
	}

	~Package() {
		delete[] description;
		description = nullptr;
	}

	const char* getDescription() const {
		return description;
	}

	double getPrice() const {
		return price;
	}

	Status getStatus() const {
		return status;
	}

	void setStatus(Status newStatus) {
		status = newStatus;
	}

	void redirect(const Person& newReceiver) {
		receiver = &newReceiver;
	}

	void editDescription(const char* newDescription) {
		delete[] description;
		description = copyStringDyn(newDescription);
	}

	void changePrice(double newPrice) {
		price = newPrice;
	}

	void printPackageInfo() const {
		std::cout << '\n';
		println("Description: {}", description);
		println("Status: {}", toString(status));
		println("Cost of Delivery: {:.2f}", price);

	    cout << "Sender   -> ";
		if (sender) sender->printPerson();

		cout << "Receiver -> ";
		if (receiver) receiver->printPerson();
	}
};

int main()
{
	Person sender("Georgi", 19);
	Person receiver("Stefo", 22);

	Package package("Backpack", 5.50, Status::Created, sender, receiver);

	println("---- Initial Shipment Information ----");
	package.printPackageInfo();
	cout << '\n';

	Person newReceiver("Misho", 99);

	package.redirect(newReceiver);
	package.editDescription("Backpack and shoes");
	package.changePrice(15.00);
	package.setStatus(Status::Shipped);

	println("---- Shipment Information after editing and redirection ----");
	package.printPackageInfo();
}


