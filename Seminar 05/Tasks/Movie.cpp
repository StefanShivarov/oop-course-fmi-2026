#include "Movie.h"
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)
const char* Utils::GenreToString(const Genre g)
{
    switch (g) {
    case Genre::Action: return "Action";
    case Genre::Comedy: return "Comedy";
    case Genre::Fantasy: return "Fantacy";
    default: return "Other";
    }
}

void Movie::free()
{
    delete[] name;
    name = nullptr;
    genre = Genre::Other;
    duration = 0;
    price = 0.0;
}

void Movie::copyFrom(const Movie& other)
{
    genre = other.genre;
    duration = other.duration;
    price = other.price;
    setName(other.name);
}

Movie::Movie() : Movie("",Genre::Other,0,0.0)
{
}

Movie::Movie(const char* name, Genre genre, int duration, double price) : genre(genre), duration(duration), price(price)
{
    setName(name);
}

Movie::Movie(const Movie& other)
{
    copyFrom(other);
}

Movie& Movie::operator=(const Movie& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
   }
    return *this;
}

Movie::~Movie()
{
    free();
}

void Movie::setName(const char* name)
{
    if (!name) {
        this->name = new char[1];
        this->name[0] = '\0';
        return;
    }
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

const char* Movie::getName() const
{
    return name;
}

Genre Movie::getGenre() const
{
    return genre;
}

int Movie::getDurationMinutes() const
{
    return duration;
}

double Movie::getTicketPrice() const
{
    return price;
}

void printMovie(const Movie& movie, std::ostream& os)
{
    os << "Name: " << movie.getName() << '\n';
    os << "Genre: " << Utils::GenreToString(movie.getGenre()) << '\n';
    os << "Duration: " << movie.getDurationMinutes() << '\n';
    os << "Price for ticket: " << movie.getTicketPrice() << '\n';
}
