#include "Film.h"
#include <cstring>
#include <iostream>
#include "Projection.h"
#pragma warning(disable : 4996)

void Film::free() {
	delete[] title;
	delete[] genre;

	title = genre = nullptr;
}

void Film::copyFrom(const Film& other)
{
	this->duration = other.duration;
	this->price = other.price;

	if (other.title != nullptr) {
		this->title = new char[strlen(other.title) + 1];
		strcpy(this->title, other.title);
	}
	else {
		this->title = new char[1];
		title[0] = '\0';
	}

	if (other.genre != nullptr) {
		this->genre = new char[strlen(other.genre) + 1];
		strcpy(this->genre, other.genre);
	}
	else {
		this->genre = new char[1];
		genre[0] = '\0';
	}
}

Film::Film() : duration(0), price(0)
{
	title = new char[1];
	title[0] = '\0';

	genre = new char[1];
	genre[0] = '\0';
}

Film::Film(const Film& other)
{
	copyFrom(other);
}

Film& Film::operator=(const Film& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Film::~Film()
{
	free();
}

Film::Film(const char* title, const char* genre, size_t duration, double price)
	: duration(duration), price(price)
{
	if (title != nullptr) {
		this->title = new char[strlen(title) + 1];
		strcpy(this->title, title);
	}
	else {
		this->title = new char[1];
		this->title[0] = '\0';
	}

	if (genre != nullptr) {
		this->genre = new char[strlen(genre) + 1];
		strcpy(this->genre, genre);
	}
	else {
		this->genre = new char[1];
		this->genre[0] = '\0';
	}
	
}

void Film::printFilm() const
{
	std::cout << "Title: " << title << " - ";
	std::cout << "Genre: " << genre << ", " << duration << '\n';
	std::cout << "Price: " << price << '\n';

}
