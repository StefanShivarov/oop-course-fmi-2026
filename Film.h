#pragma once
#include"Genre.h"
#include"Time.h"

class Film
{
private:
	char* title = nullptr;
	Type genre = Type::Action;
	Time t;
	double price = 0;

	void copyFrom(const Film& other);
	void free();

public:
	Film();
	Film(const char* title, Type genre, Time t, double price);
	Film(const char* title, const char* genre, Time t, double price);

	Film(const Film& other);
	Film& operator=(const Film& other);
	~Film();

	void setTitle(const char* title);
	void setPrice(double price);
	void setGenre(const char* genre);

	const char* getTitle() const;
	Type getGenre() const;
	Time getTime() const;
	double getPrice() const;

	void printFilm()const;
};

