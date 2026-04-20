#include "Movie.h"
#include <cstring>

namespace {
    char* copyDynamicCharArray(const char* str) {
        if (!str) {
            char* result = new char[1];
            result[0] = '\0';
            return result;
        }

        size_t len = strlen(str);
        char* result = new char[len + 1];
        strcpy(result, str);
        return result;
    }

    const char* parseGenreToString(Genre g) {
        using enum Genre;
        switch (g) {
        case ACTION: return "Action";
        case DRAMA: return "Drama";
        case THRILLER: return "Thriller";
        case COMEDY: return "Comedy";
        case HORROR: return "Horror";
        case HISTORICAL: return "Historical";
        case SCIFI: return "Sci-Fi";
        default: return "Other";
        }
    }
}

void Movie::copyFrom(const Movie& other) {
    title = copyDynamicCharArray(other.title);
    durationMinutes = other.durationMinutes;
    ticketPrice = other.ticketPrice;
    genre = other.genre;
}

void Movie::free() {
    delete[] title;
    title = nullptr;
}

Movie::Movie() : Movie("", Genre::OTHER, 0, 0.0) {}

Movie::Movie(const char* title, Genre genre, unsigned durationMinutes, double ticketPrice)
    : genre(genre), durationMinutes(durationMinutes), ticketPrice(ticketPrice) {
    this->title = copyDynamicCharArray(title);
}

Movie::Movie(const Movie& other)
    : genre(other.genre), durationMinutes(other.durationMinutes), ticketPrice(other.ticketPrice) {
    title = copyDynamicCharArray(other.title);
}

Movie& Movie::operator=(const Movie& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Movie::~Movie() {
    free();
}

const char* Movie::getTitle() const {
    return title;
}

unsigned Movie::getDurationMinutes() const {
    return durationMinutes;
}

double Movie::getTicketPrice() const {
    return ticketPrice;
}

Genre Movie::getGenre() const {
    return genre;
}

void printMovie(const Movie& movie, std::ostream& os) {
    os << "Title: " << movie.getTitle() << '\n'
        << "Genre: " << parseGenreToString(movie.getGenre()) << '\n'
        << "durationMinutes: " << movie.getDurationMinutes() << " min\n"
        << "Ticket price: " << movie.getTicketPrice() << '\n';
}
