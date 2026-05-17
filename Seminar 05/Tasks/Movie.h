#pragma once
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)


enum class Genre {
	Action, Fantasy, Comedy, Other
};

namespace Utils {
	const char* GenreToString(const Genre g);
}

class Movie {
	char* name = nullptr;
	Genre genre;
	int duration;
	double price;

	void free();
	void copyFrom(const Movie& other);
public:
	Movie();
	Movie(const char* name, Genre genre, int duration, double price);
	Movie(const Movie& other);
	Movie& operator=(const Movie& other);
	~Movie();

	void setName(const char* name);

	const char* getName() const;
	Genre getGenre() const;
	int getDurationMinutes() const;
	double getTicketPrice() const;

};

void printMovie(const Movie& movie, std::ostream& os = std::cout);