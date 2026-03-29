#pragma once
#include <iostream>

enum class Genre {
    ACTION, COMEDY, DRAMA, THRILLER, HORROR, HISTORICAL, SCIFI, OTHER
};

class Movie
{
private:
    char* title;
    Genre genre;
    unsigned durationMinutes;
    double ticketPrice;

    void copyFrom(const Movie& other);
    void free();

public:
    Movie();
    Movie(const char* title, Genre genre, unsigned duration, double ticketPrice);
    Movie(const Movie& other);
    Movie& operator=(const Movie& other);
    ~Movie();

    const char* getTitle() const;
    Genre getGenre() const;
    unsigned getDurationMinutes() const;
    double getTicketPrice() const;

};

void printMovie(const Movie& movie, std::ostream& os = std::cout);
