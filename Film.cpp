#define _CRT_SECURE_NO_WARNINGS
#include "Film.h"
#include<cstring>
#include<print>

Film::Film():genre(Type::Action), price(0)
{
	title = new char[1];
	title[0] = '\0';

	t.hour = 0;
	t.min = 0;
}

Film::Film(const char* title, Type genre, Time t, double price) :genre(genre), t(t)
{
	setTitle(title);
	setPrice(price);
}

Film::Film(const char* title, const char* genre, Time t, double price):t(t)
{
	setTitle(title);
	setPrice(price);
	setGenre(genre);
}

void Film::setGenre(const char* genre)
{
	if (genre == nullptr)
	{
		return;
	}

	this->genre = Genre::convertStringToType(genre);
}

void Film::setTitle(const char* title)
{
	if (this->title != nullptr)
	{
		delete[] this->title;
	}

	this->title = new char[strlen(title) + 1];
	strcpy(this->title, title);
}

void Film::setPrice(double price)
{
	if (price < 0)
	{
		return;
	}

	this->price = price;
}

void Film::copyFrom(const Film& other)
{
	setTitle(other.title);
	genre = other.genre;
	t = other.t;
	setPrice(other.price);
}

void Film::free()
{
	delete[]title;
	title = nullptr;
}

Film::~Film()
{
	free();
}

Film::Film(const Film& other)
{
	copyFrom(other);
}

Film& Film::operator=(const Film& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

const char* Film::getTitle() const
{
	return title;
}

Type Film::getGenre() const
{
	return genre;
}

Time Film::getTime() const
{
	return t;
}

double Film::getPrice() const
{
	return price;
}

void Film::printFilm()const
{
	std::println("Title: {}, Genre: {}", title, Genre::convertTypeToString(genre));
	std::print("Duration:");
	t.printTime();
	std::println("Price: {}", price);
	std::println();
}