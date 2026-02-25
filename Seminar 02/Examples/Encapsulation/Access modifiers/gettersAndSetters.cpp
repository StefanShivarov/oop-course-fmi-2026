#include <iostream>

class Date {
private:
    int year = 1970;
    int month = 1;
    int day = 1;

    int DAYS_IN_MONTH[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool isLeapYear(int y) const {
        return (y % 4 == 0) && (y % 100 != 0 || y % 400 == 0);
    }

    int getMaxDaysForMonth(int y, int m) const {
        if (m < 1 || m > 12) {
            return 0;
        }

        if (m == 2 && isLeapYear(y)) {
            return 29;
        }

        return DAYS_IN_MONTH[m - 1];
    }

    bool isValidCombination(int y, int m, int d) const {
        if (y < 1) {
            return false;
        }

        if (m < 1 || m > 12) {
            return false;
        }

        int maxDays = getMaxDaysForMonth(y, m);
        if (d < 1 || d > maxDays) {
            return false;
        }

        return true;
    }

public:
    bool setAll(int y, int m, int d) {
        if (!isValidCombination(y, m, d)) {
            return false;
        }

        year = y;
        month = m;
        day = d;
        return true;
    }

    bool setYear(int y) {
        if (!isValidCombination(y, month, day)) {
            return false;
        }

        year = y;
        return true;
    }

    bool setMonth(int m) {
        if (!isValidCombination(year, m, day)) {
            return false;
        }

        month = m;
        return true;
    }

    bool setDay(int d) {
        if (!isValidCombination(year, month, d)) {
            return false;
        }

        day = d;
        return true;
    }

    int getYear() const {
        return year;
    }

    int getMonth() const {
        return month;
    }

    int getDay() const {
        return day;
    }
};

class Event {
private:
    Date date;
    int startHour = 9;         // 0..23
    double ticketPrice = 0.0;  // >= 0

public:
    const Date& getDate() const {
        return date;
    }

    int getStartHour() const {
        return startHour;
    }

    double getTicketPrice() const {
        return ticketPrice;
    }

    void setDate(const Date& date) {
        // we must use this->date here, because the argument has the same name as Event::date
        // otherwise date = date will just assign the argument to itself
        this->date = date;
    }

    bool setStartHour(int hour) {
        if (hour < 0 || hour > 23) {
            return false;
        }

        startHour = hour;
        return true;
    }

    bool setTicketPrice(double price) {
        if (price < 0) {
            return false;
        }

        ticketPrice = price;
        return true;
    }
};

int main() {
    Date d;
    std::cout << d.getDay() << "." << d.getMonth() << "." << d.getYear() << "\n";

    if (!d.setAll(2024, 2, 29)) {
        std::cout << "Invalid date\n";
    }

    Event e;
    e.setDate(d);

    if (!e.setStartHour(19)) {
        std::cout << "Invalid hour\n";
    }

    if (!e.setTicketPrice(35.50)) {
        std::cout << "Invalid price\n";
    }

    std::cout << e.getDate().getDay() << "."
              << e.getDate().getMonth() << "."
              << e.getDate().getYear() << "  "
              << e.getStartHour() << ":00  "
              << e.getTicketPrice() << " lv\n";

    // invalid examples
    if (!d.setYear(2023)) {
        std::cout << "Can't change to 2023 (Feb 29 would break)\n";
    }

    if (!e.setStartHour(50)) {
        std::cout << "Invalid hour\n";
    }

    if (!e.setTicketPrice(-10)) {
        std::cout << "Invalid price\n";
    }
}
