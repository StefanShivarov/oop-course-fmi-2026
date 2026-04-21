#pragma once
enum class Type
{
	SEMINAR, CONCERT, SPORT, OTHER
};

class Event
{
private:
	char* name = nullptr;
	char* description = nullptr;
	Type type;
	double basePrice;
	unsigned capacity;
	double price;


	void copyDynamicMemory(const Event& other);
	void copyFrom(const Event& other);
	void moveFrom(Event&& other) noexcept;
	void free();
public:
	Event(const char* name,const char* descrption, Type type, double basePrice, double price, unsigned capacity );
	Event(const Event& other);
	Event& operator=(const Event& other);
	Event(Event&& other) noexcept;
	Event& operator=(Event&& other)noexcept;
	~Event();

	const char* getName() const;
	const char* getDescription() const;
	Type getType()const;
	double getBasePrice()const;
	unsigned getCapacity()const;
	double getPrice()const;

};
