#include <iostream>
#include <cstring>
#include <print>

#pragma warning (disable : 4996)

class Person {
private:
    char* name;
	int age;

public:
	Person() : age(0) {
		name = new char[1];
		name[0] = '\0';
	}

	Person(const char* name, int age) : age(age) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}

	const char* getName() const {
		return name;
	} 

	void setName(const char* newName) {
		if (newName == name) return;

		delete[] name;
		name = new char[strlen(newName) + 1];
		strcpy(name, newName);
	}

	int getAge() const {
		return age;
	}

	void setAge(int newAge) {
		age = newAge;
	}

	~Person() {
		delete[] name;
	}

	void print() const {
		std::println("Name: {}, Age: {}", name, age);
	}
};

enum class ParcelStatus {
	Created,
	InTransit,
	Delivered
};

const char* getParcelStatusString(ParcelStatus status) {
	switch (status) {
	case ParcelStatus::Created:
		return "Created";
	case ParcelStatus::InTransit:
		return "In Transit";
	case ParcelStatus::Delivered:
		return "Delivered";
	default:
		return "Unknown";
	}
}

class Parcel {
private:
	Person* sender;
	Person* recipient;

	char* description;
	double price;
	double weight;
	ParcelStatus status;

public:
	Parcel(Person* sender, Person* recipient, const char* description, double price, double weight)
		: sender(sender), recipient(recipient), price(price), weight(weight), status(ParcelStatus::Created) {
		this->description = new char[strlen(description) + 1];
		strcpy(this->description, description);
	}

	const char* getDescription() const {
		return description;
	}

	void setDescription(const char* newDescription) {
		if (newDescription == description) return;

		delete[] description;
		description = new char[strlen(newDescription) + 1];
		strcpy(description, newDescription);
	}

	double getPrice() const {
		return price;
	}

	void setPrice(double newPrice) {
		price = newPrice;
	}

	double getWeight() const {
		return weight;
	}

	void setWeight(double newWeight) {
		weight = newWeight;
	}

	ParcelStatus getStatus() const {
		return status;
	}

	void setStatus(ParcelStatus newStatus) {
		status = newStatus;
	}

	void redirect(Person& newRecipient) { // Not deleting old recipient, he is still a valid person
		if (status == ParcelStatus::Delivered) return;
		
		recipient = &newRecipient;
	}

	void print() const {
		std::println("Sender: {}, Recipient: {}, Description: {}, Price: {}, Weight: {}, Status {}",
			sender->getName(), recipient->getName(), description, price, weight, getParcelStatusString(status));
	}

	~Parcel() {
		delete[] description;
	}
};

int main()
{
	Person sender("Alice", 30);
	Person recipient("Bob", 25);
	Person newRecipient("Charlie", 28);

	Parcel parcel(&sender, &recipient, "Books", 20.0, 2.5);

	parcel.print();
	parcel.setPrice(25.0);
	parcel.setDescription("Books and CDs");

	parcel.redirect(newRecipient);
	parcel.print();
}