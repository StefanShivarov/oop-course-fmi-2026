#include <iostream>
using namespace std;

struct Date {
    int day = 1;
    int month = 1;
    int year = 0;
    bool operator==(const Date& other) const {
        if (this -> day != other.day || this -> month != other.month || this -> year != other.year) {
            return false;
        }
        return true;
    }
    string toString() const {
        return format("{:02}.{:02}.{:04}", this -> day, this -> month, this -> year);
    }
};
class Movie {
    char* title;
    char* genre;
    int length;
    double ticketPrice;
    public:
    Movie(const char* title, const char* genre, const int length, const double ticketPrice) : title(nullptr), genre(nullptr), length(length), ticketPrice(ticketPrice) {
        this -> title = new char[strlen(title) + 1];
        strcpy(this -> title, title);
        this -> genre = new char[strlen(genre) + 1];
        strcpy(this -> genre, genre);
    };
    Movie(const Movie& other) : title(nullptr), genre(nullptr), length(other.length), ticketPrice(other.ticketPrice) {
        this -> title = new char[strlen(other.title) + 1];
        strcpy(this -> title, other.title);
        this -> genre = new char[strlen(other.genre) + 1];
        strcpy(this -> genre, other.genre);
    }
    Movie& operator=(const Movie& other) {
        if (this != &other) {
            delete[] title;
            delete[] genre;
            this -> title = new char[strlen(other.title) + 1];
            strcpy(this -> title, other.title);
            this -> genre = new char[strlen(other.genre) + 1];
            strcpy(this -> genre, other.genre);
            this -> length = other.length;
            this -> ticketPrice = other.ticketPrice;
        }
        return *this;
    }
    ~Movie() {
        delete[] title;
        delete[] genre;
    }
    bool operator==(const Movie& other) const {
        if (strcmp(this -> title, other.title) != 0 || strcmp(this -> genre, other.genre) != 0 || this -> length != other.length || this -> ticketPrice != other.ticketPrice) {
            return false;
        }
        return true;
    }
    string toString() const {
        return format("{}, genre: {}, {} minutes long, price: {}", this -> title, this -> genre, this -> length, this -> ticketPrice);
    }
};
class CinemaHall {
    int id = 0;
    int seatCount = 0;
    public:
    CinemaHall(const int id, const int seatCount) : id(id), seatCount(seatCount) {};
    bool operator==(const CinemaHall& other) const {
        if (this -> id != other.id || this -> seatCount != other.seatCount) {
            return false;
        }
        return true;
    }
    string toString() const {
        return format("CinemaHall: {}, {} seats", this -> id, this -> seatCount);
    }
    int getSeatCount() const {
        return seatCount;
    }
};
class Projection {
    const Movie *movie{};
    const CinemaHall *cinemaHall{};
    bool* seats{};
    int seatCount = 0;
    Date date;
    int hour = 0;
    public:
    Projection() = default;
    Projection(const Movie* movie, const CinemaHall* cinemaHall, const Date& date, const int hour) : cinemaHall(cinemaHall), date(date), hour(hour) {
        this -> movie = movie;
        seatCount = cinemaHall->getSeatCount();
        seats = new bool[seatCount]{false};
    }
    Projection(const Projection& other) : cinemaHall(other.cinemaHall), seatCount(other.seatCount), date(other.date), hour(other.hour) {
        this -> movie = other.movie;
        seats = new bool[seatCount];
        for (int i = 0; i < seatCount; i++) {
            seats[i] = other.seats[i];
        }
    }
    Projection& operator=(const Projection& other) {
        if (this != &other) {
            delete[] seats;
            this -> movie = other.movie;
            this -> cinemaHall = other.cinemaHall;
            this -> seatCount = other.seatCount;
            seats = new bool[seatCount];
            for (int i = 0; i < seatCount; i++) {
                seats[i] = other.seats[i];
            }
            this -> date = other.date;
            this -> hour = other.hour;
        }
        return *this;
    }
    ~Projection() {
        delete[] seats;
    }
    bool operator==(const Projection& other) const {
        if (!(this -> movie == other.movie) || !(this -> cinemaHall == other.cinemaHall) || this -> seatCount != other.seatCount || !(this -> date == other.date) || this -> hour != other.hour) {
            return false;
        }
        return true;
    }
    int getFreeSeatsCount() const {
        int counter = 0;
        for (int i = 0; i < seatCount; i++) {
            if (!seats[i]) {
                counter++;
            }
        }
        return counter;
    }
    string toString() const {
        return format("Watch {} in {}, at {}, from {}, {} seats available", movie -> toString(), cinemaHall -> toString(), date.toString(), hour, getFreeSeatsCount());
    }
    static void getInfo(const Projection& other) {
        println("{}", other.toString());
    }
    bool isSeatFree(const int seat) const {
        if (seat < 0 || seat >= seatCount) {
            return false;
        }
        return !seats[seat];
    }
    void reserve(const int seat) {
        if (seat < 0 || seat >= seatCount) {
            println("Invalid seat!");
            return;
        }
        if (seats[seat]) {
            println("Seat already taken!");
            return;
        }
        seats[seat] = true;
    }
    void freeSeat(const int seat) {
        if (seat < 0 || seat >= seatCount) {
            println("Invalid seat!");
            return;
        }
        if (!seats[seat]) {
            println("Seat already free!");
            return;
        }
        seats[seat] = false;
    }
};
class Serializer {
    Projection* projection;
    int size;
    public:
    Serializer() : projection(nullptr), size(0) {};
    ~Serializer() {
        delete[] projection;
    }
    void add(const Projection& other) {
        auto* newArray = new Projection[size + 1];
        for (int i = 0; i < size; i++) {
            newArray[i] = this -> projection[i];
        }
        newArray[size++] = other;
        delete[] this -> projection;
        this -> projection = newArray;
    }
    void remove(const Projection& other) {
        if (size >= 1) {
            auto* newArray = new Projection[size - 1];
            int pos = 0;
            bool found = false;
            for (int i = 0; i < size; i++) {
                if (!(this -> projection[i] == other)) {
                    newArray[pos++] = this -> projection[i];
                }
                else {
                    found = true;
                }
            }
            if (!found) {
                delete[] newArray;
                return;
            }
            size--;
            delete[] this -> projection;
            this -> projection = newArray;
        }
    }
    void print() const {
        for (int i = 0; i < size; i++) {
            println("{}", this -> projection[i].toString());
        }
    }

};
int main() {
}