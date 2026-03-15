#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Time {
    private:
        int hours;
        int minutes;
        int seconds;
    public:
        int getHours() const {
            return hours;
        }
        int getMinutes() const {
            return minutes;
        }
        int getSeconds() const {
            return seconds;
        }
        bool setHours(const int hours) {
            if (hours >= 0 && hours <= 23) {
                this -> hours = hours;
                return true;
            }
            return false;
        }
        bool setMinutes(const int minutes) {
            if (minutes >= 0 && minutes <= 59) {
                this -> minutes = minutes;
                return true;
            }
            return false;
        }
        bool setSeconds(const int seconds) {
            if (seconds >= 0 && seconds <= 59) {
                this -> seconds = seconds;
                return true;
            }
            return false;
        }
        int toSeconds() const {
            return hours * 60 * 60 + minutes * 60 + seconds;
        }
        void addSeconds(const int delta) {
            seconds += delta;
            while (seconds >= 60) {
                seconds -= 60;
                minutes++;
            }
            while (minutes >= 60) {
                minutes -= 60;
                hours++;
            }
            while (hours >= 24) {
                hours -= 24;
            }
        }
        bool isBefore(const Time& otherTime) const {
            if (this -> hours != otherTime.hours) {
                return this -> hours < otherTime.hours;
            }
            if (this -> minutes != otherTime.minutes) {
                return this -> minutes < otherTime.minutes;
            }
            if (this -> seconds != otherTime.seconds) {
                return this -> seconds < otherTime.seconds;
            }
            return true;
        }
        bool isAfter(const Time& otherTime) const {
            if (this -> hours != otherTime.hours) {
                return this -> hours > otherTime.hours;
            }
            if (this -> minutes != otherTime.minutes) {
                return this -> minutes > otherTime.minutes;
            }
            if (this -> seconds != otherTime.seconds) {
                return this -> seconds > otherTime.seconds;
            }
            return true;
        }
        bool isEqual(const Time& otherTime) const {
            return this -> hours == otherTime.hours && this -> minutes == otherTime.minutes && this -> seconds == otherTime.seconds;
        }
        bool validate() const {
            return this -> getHours() <= 23 && this -> getHours() >= 0 &&
                this -> getMinutes() <= 59 && this -> getMinutes() >= 0 &&
                    this -> getSeconds() <= 59 && this -> getSeconds() >= 0;
        }
};
class Schedule {
    string room;
    string day;
    string subject;
    Time startTime;
    Time endTime;
public:
    string getRoom() const {
        return room;
    }
    bool setRoom(const string &room) {
        if (room.empty()) {
            return false;
        }
        this -> room = room;
        return true;
    }
    string getDay() const {
        return day;
    }
    bool setDay(const string &day) {
        if (day != "MONDAY" && day != "TUESDAY" && day != "WEDNESDAY" && day != "THURSDAY" && day != "FRIDAY") {
            return false;
        }
        this -> day = day;
        return true;
    }
    string getSubject() const {
        return subject;
    }
    bool setSubject(const string &subject) {
        if (subject != "OOP" && subject != "DIS2" && subject != "DSTR2" && subject != "GEOMETRY") {
            return false;
        }
        this -> subject = subject;
        return true;
    }
    Time getStartTime() const {
        return startTime;
    }
    bool setStartTime(const Time &startTime) {
        if (!startTime.validate()) {
            return false;
        }
        this -> startTime = startTime;
        return true;
    }
    Time getEndTime() const {
        return endTime;
    }
    bool setEndTime(const Time &endTime) {
        if (!endTime.validate()) {
            return false;
        }
        this -> endTime = endTime;
        return true;
    }
};
void resize(Schedule*& arr, const size_t size) {
    Schedule* new_arr = new Schedule[size + 1];
    for (size_t i = 0; i < size; i++) {
        new_arr[i] = arr[i];
    }
    delete [] arr;
    arr = new_arr;
}
void resizeSet(string*& arr, const size_t size) {
    string* new_arr = new string[size + 1];
    for (size_t i = 0; i < size; i++) {
        new_arr[i] = arr[i];
    }
    delete [] arr;
    arr = new_arr;
}
void addToSet(const string& element, string*& arr, size_t& size) {
    bool met = false;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == element) {
            met = true;
            break;
        }
    }
    if (!met) {
        resizeSet(arr, size);
        arr[size++] = element;
    }
}
bool noOverlap(const Schedule* arr, const size_t size, const string& room, const string& day, const Time& startTime, const Time& endTime) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i].getRoom() == room && arr[i].getDay() == day) {
            if (startTime.isBefore(arr[i].getStartTime()) && endTime.isAfter(arr[i].getStartTime())) {
                return false;
            }
            if (startTime.isEqual(arr[i].getStartTime()) && endTime.isBefore(arr[i].getEndTime())) {
                return false;
            }
            if (startTime.isAfter(arr[i].getStartTime()) && endTime.isBefore(arr[i].getEndTime())) {
                return false;
            }
            if (startTime.isEqual(arr[i].getStartTime()) && endTime.isEqual(arr[i].getEndTime())) {
                return false;
            }
            if (startTime.isBefore(arr[i].getStartTime()) && endTime.isAfter(arr[i].getEndTime())) {
                return false;
            }
            if (startTime.isBefore(arr[i].getEndTime()) && endTime.isEqual(arr[i].getEndTime())) {
                return false;
            }
            if (startTime.isBefore(arr[i].getEndTime()) && endTime.isAfter(arr[i].getEndTime())) {
                return false;
            }
        }
    }
    return true;
}
bool add(const string& room, const string& day, const string& subject, const Time& startTime, const Time& endTime, Schedule*& arr, size_t& size) {
    Schedule *schedule = new Schedule();
    if (!schedule->setRoom(room) || !schedule->setDay(day) || !schedule->setSubject(subject) || !schedule->setStartTime(startTime) || !schedule->setEndTime(endTime) || startTime.isAfter(endTime) || !noOverlap(arr, size, room, day, startTime, endTime)) {
        delete schedule;
        return false;
    }
    resize(arr, size);
    arr[size++] = *schedule;
    delete schedule;
    return true;
}
int strToInt(const string& str) {
    int res = 0;
    const size_t n = str.length();
    for (size_t i = 0; i < n; i++) {
        res = res * 10 + str[i] - '0';
    }
    return res;
}
int main() {
    Schedule *schedule = new Schedule[0];
    size_t n = 0;
    string room;
    string day;
    string subject;
    Time startTime;
    Time endTime;
    int startH, startM, startS;
    int endH, endM, endS;
    ifstream ifs("schedule.txt");
    if (!ifs.is_open()) {
        println("Error while reading!");
        delete[] schedule;
        return 1;
    }
    string line;
    while (getline(ifs, line)) {
        for (char& c : line) {
            if (c == ',' || c == ':') {
                c = ' ';
            }
        }
        stringstream ss(line);
        ss >> room >> day >> subject >> startH >> startM >> startS >> endH >> endM >> endS;
        startTime.setHours(startH);
        startTime.setMinutes(startM);
        startTime.setSeconds(startS);
        endTime.setHours(endH);
        endTime.setMinutes(endM);
        endTime.setSeconds(endS);
        add(room, day, subject, startTime, endTime, schedule, n);
    }
    ifs.close();
    // for (size_t i = 0; i < n; i++) {
    //     println("{}, {}, {}, {:02}:{:02}:{:02}, {:02}:{:02}:{:02}", schedule[i].getRoom(), schedule[i].getDay(), schedule[i].getSubject(), schedule[i].getStartTime().getHours(), schedule[i].getStartTime().getMinutes(), schedule[i].getStartTime().getSeconds(), schedule[i].getEndTime().getHours(), schedule[i].getEndTime().getMinutes(), schedule[i].getEndTime().getSeconds());
    // }
    println();
    string days[] = {"MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY"};
    for (int i = 0; i < 5; i++) {
        println("{}:", days[i]);
        for (size_t j = 0; j < n; j++) {
            if (schedule[j].getDay() == days[i]) {
                println("{}, {}, {:02}:{:02}:{:02}, {:02}:{:02}:{:02}", schedule[i].getRoom(), schedule[i].getSubject(), schedule[i].getStartTime().getHours(), schedule[i].getStartTime().getMinutes(), schedule[i].getStartTime().getSeconds(), schedule[i].getEndTime().getHours(), schedule[i].getEndTime().getMinutes(), schedule[i].getEndTime().getSeconds());
            }
        }
    }
    println();
    string* set = new string[0];
    size_t m = 0;
    for (size_t i = 0; i < n; i++) {
        addToSet(schedule[i].getRoom(), set, m);
    }
    for (size_t i = 0; i < m; i++) {
        println("{}:", set[i]);
        for (size_t j = 0; j < n; j++) {
            if (schedule[j].getRoom() == set[i]) {
                println("{}, {}, {:02}:{:02}:{:02}, {:02}:{:02}:{:02}", schedule[j].getDay(), schedule[j].getSubject(),
                        schedule[j].getStartTime().getHours(), schedule[j].getStartTime().getMinutes(),
                        schedule[j].getStartTime().getSeconds(), schedule[j].getEndTime().getHours(),
                        schedule[j].getEndTime().getMinutes(), schedule[j].getEndTime().getSeconds());
            }
        }
    }
    delete[] schedule;
}