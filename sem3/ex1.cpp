#include <iostream>
#include <print>
#include <format>
#include <cstring>
#pragma warning(disable : 4996) // za strcpy

using std::cin;
using std::cout;
using std::println;;

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

enum class Status {
	Created, Processing, Shipped, Delivered, Delayed, Returned
};

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
private:
	char* name = nullptr;
	int age = 0;

public:
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
		delete[]name;
		name = utils::copyDynamicString(newName);
	}

	void setAge(int newAge) {
		if (newAge < 0) {
			return;
		}

		age = newAge;
	}

	void printPerson() const {
		std::println("Name: {}, age: {}", name, age);
	}
};

class Shipment {
private:
	char* description = nullptr;
	double deliveryCost;
	Status status;
	const Person* sender;
	const Person* receiver;

public:
	Shipment(const char* description, double deliveryCost, Status status, const Person& sender, const Person& receiver) 
		: deliveryCost(deliveryCost), status(status), sender(&sender), receiver(&receiver) {

		this->description = utils::copyDynamicString(description);
	}

	~Shipment() {
		delete[] description;
		description = nullptr;
	}

	const char* getDescription() const {
		return description;
	}

	double getDeliveryCost() const {
		return deliveryCost;
	}

	Status getStatus() const {
		return status;
	}

	void setStatus(Status newStatus) {
		status = newStatus;
	}

	void redirection(const Person& newReceiver) {
		receiver = &newReceiver;
	}

	void editDescription(const char* newDescription) {
		delete[] description;
		description = utils::copyDynamicString(newDescription);
	}

	void changeCostDelivery(double newCost) {
		deliveryCost = newCost;
	}

	void printShipmentInfo() const {
		cout << '\n';
		println("Description: {}", description);
		println("Status: {}", toString(status));
		println("Cost of Delivery: {:.2f}", deliveryCost);

		cout << "Sender   -> ";
		if(sender) sender->printPerson();

		cout << "Receiver -> ";
		if(receiver) receiver->printPerson();
	}
};

int main()
{
	Person sender("Magi", 29);
	Person receiver("Sevim", 19);

	Shipment shipment("Phone", 9.99, Status::Created, sender, receiver);

	println("---- Initial Shipment Information ----");
	shipment.printShipmentInfo();
	cout << '\n';

	Person newReceiver("Ivo", 35);

	shipment.redirection(newReceiver);
	shipment.editDescription("Phone and charger");
	shipment.changeCostDelivery(15.00);
	shipment.setStatus(Status::Shipped);

	std::println("---- Shipment Information after editing and redirection ----");
	shipment.printShipmentInfo();

}