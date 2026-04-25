#include "Movie.h"

void Movie::copyDynamicMemory(const Movie& other) {
	this->title = new char[std::strlen(other.title) + 1];
	std::strcpy(this->title, other.title);

	this->genre = new char[std::strlen(other.genre) + 1];
	std::strcpy(this->genre, other.genre);
}

void Movie::freeDynamicMemory() {
	delete[] title;
	delete[] genre;
}

Movie::Movie(const char* title, const char* genre, unsigned dur, double price) : duration(dur), ticketPrice(price) {
	this->title = new char[std::strlen(title) + 1];
	std::strcpy(this->title, title);

	this->genre = new char[std::strlen(genre) + 1];
	std::strcpy(this->genre, genre);
}

Movie::Movie(const Movie & other) : duration(other.duration), ticketPrice(other.ticketPrice) {
	copyDynamicMemory(other);
}

Movie& Movie::operator=(const Movie& other) {
	if (this != &other) {
		this->duration = other.duration;
		this->ticketPrice = other.ticketPrice;

		freeDynamicMemory();
		copyDynamicMemory(other);
	}

	return *this;
}

Movie::~Movie() {
	freeDynamicMemory();
}

const char* Movie::getTitle() const {
	return title;
}

const char* Movie::getGenre() const {
	return genre;
}

unsigned Movie::getDuration() const {
	return duration;
}

double Movie::getTickerPrice() const {
	return ticketPrice;
}
