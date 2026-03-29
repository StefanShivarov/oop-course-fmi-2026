#include <iostream>
#include "task1.h"
using std::cin;
using std::cout;
using std::endl;

int Time::getHours() const{
    return hours;
}

int Time::getMinutes() const {
    return minutes;
}
    
int Time::getSeconds() const {
    return seconds;
}

void Time::setHours(int hours) {
    if (hours >= 0 && hours < 24) {
        this->hours = hours;
    }
}

void Time::setMinutes(int minutes) {
    if (minutes >= 0 && minutes < 60) {
        this->minutes = minutes;
    }
}

void Time::setSeconds(int seconds) {
    if (seconds >= 0 && seconds < 60) {
        this->seconds = seconds;
    }
}

int Time::toSeconds() const {
    return getHours() * 3600 + getMinutes() * 60 + getSeconds();
}

void Time::addSeconds(int delta) {
    int newTime = toSeconds() + delta;
    int newHours = 0;
    int newMinutes = 0;
    int newSeconds = 0;

    if (newTime > 24 * 3600) {
        newTime -= 24 * 3600;
    }
    else if (newTime == 24 * 3600) {
        newTime = 0;
    }

    newHours = newTime / 3600;
    newMinutes = (newTime % 3600) / 60;
    newSeconds = (newTime % 3600) % 60;
    setHours(newHours);
    setMinutes(newMinutes);
    setSeconds(newSeconds);
}

bool Time::isBefore(const Time& other) const {
    return toSeconds() < other.toSeconds();
}

bool Time::isAfter(const Time& other) const {
    return toSeconds() > other.toSeconds();
}

void Time::writeTime(std::ostream& out) const {
    if (hours < 10) {
        out << "0";
    }
    out << hours << ":";

    if (minutes < 10) {
        out << "0";
    }
    out << minutes << ":";

    if (seconds < 10) {
        out << "0";
    }
    out << seconds;
}

bool Time::isValidTime(int hours, int minutes, int seconds) const {
    if (hours < 0 || hours > 24 || minutes < 0 || minutes > 60 || seconds < 0 || seconds > 60) {
        return false;
    }
    return true;
}

void Time::readTime(std::istream& in) {
    int hours, minutes, seconds;
    char symbol1, symbol2;

    while (true) {
        in >> hours >> symbol1 >> minutes >> symbol2 >> seconds;
        
        if (in.fail()) {
            cout << "invalid input! try again." << endl;
            in.clear();
            in.ignore(1000, '\n');
            continue;
        }

        bool validation = isValidTime(hours, minutes, seconds);
        if (symbol1 != ':' || symbol2 != ':' || !validation) {
            cout << "invalid input! try again." << endl;
            in.clear();
            in.ignore(1000, '\n');
            continue;
        }

        setHours(hours);
        setMinutes(minutes);
        setSeconds(seconds);
        break;
    }
}

void swapTimes(Time& time1, Time& time2) {
    Time temp = time1;
    time1 = time2;
    time2 = temp;
}

void sortTimes(Time* times, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (times[j].toSeconds() > times[j+1].toSeconds()) {
                swapTimes(times[j], times[j+1]);
            }
        }
    }
}

// int main() {
//     int n;
//     cout << "enter a number of hours: ";
//     cin >> n;
//     Time* times = new Time[n];

//     cout << "enter in a format HH:MM:SS: ";
//     for (int i = 0; i < n; i++) {
//         times[i].readTime(cin);
//     }

//     sortTimes(times, n);
//     cout << endl;
//     for (int i = 0; i < n; i++) {
//         times[i].writeTime(cout);
//         cout << endl;
//     }

//     delete[] times;
// }