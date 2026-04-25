#pragma once

#include <cstring>
#pragma warning (disable: 4996)

class Movie {
private:
	char* title;
	char* genre;
	unsigned duration;
	double ticketPrice;

	void copyDynamicMemory(const Movie& other);
	void freeDynamicMemory();

public:
	Movie() = delete;
	Movie(const char* title, const char* genre, unsigned duration, double ticketPrice);
	Movie(const Movie& other);
	Movie& operator=(const Movie& other);
	~Movie();

	const char* getTitle() const;
	const char* getGenre() const;
	unsigned getDuration() const;
	double getTickerPrice() const;
};

