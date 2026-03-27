#include<iostream>

using std::cin;
using std::cout;
using std::endl;

enum class Day {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY
};

enum class Subject {
    OOP,
    DSTR2,
    DIS2,
    COMPUTER_ENGLISH,
    GEOMETRY
};

std::ostream &operator<<(std::ostream &os, const Day d) {
    switch (d) {
        case Day::MONDAY: os << "Monday";
            break;
        case Day::TUESDAY: os << "Tuesday";
            break;
        case Day::WEDNESDAY: os << "Wednesday";
            break;
        case Day::THURSDAY: os << "Thursday";
            break;
        case Day::FRIDAY: os << "Friday";
            break;
        default: os << "Unknown";
            break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Subject s) {
    switch (s) {
        case Subject::COMPUTER_ENGLISH: os << "Computer english";
            break;
        case Subject::DIS2: os << "DIS2";
            break;
        case Subject::DSTR2: os << "DSTR2";
            break;
        case Subject::GEOMETRY: os << "Geometry";
            break;
        case Subject::OOP: os << "OOP";
            break;
        default: os << "Unknown";
            break;
    }
    return os;
}

class Time {
private:
    int hour_ = 0;
    int minute_ = 0;
    int second_ = 0;

public:
    void setHour(const int hour) {
        if (hour < 0 || hour > 23) {
            cout << "Invalid input" << endl;
            return;
        }
        this->hour_ = hour;
    }

    void setMinute(const int minute) {
        if (minute < 0 || minute > 59) {
            cout << "Invalid input" << endl;
            return;
        }
        this->minute_ = minute;
    }

    void setSecond(const int second) {
        if (second < 0 || second > 59) {
            cout << "Invalid input" << endl;
            return;
        }
        this->second_ = second;
    }

    void setTime(const int hour, const int minute, const int second) {
        setHour(hour);
        setMinute(minute);
        setSecond(second);
    }

    int getHour() const {
        return this->hour_;
    }

    int getMinute() const {
        return this->minute_;
    }

    int getSecond() const {
        return this->second_;
    }

    long toSeconds() const {
        return (hour_ * 3600 + minute_ * 60 + second_);
    }

    bool isBefore(const Time &other) const {
        return toSeconds() < other.toSeconds();
    }

    bool isAfter(const Time &other) const {
        return toSeconds() > other.toSeconds();
    }

    void print() const {
        cout << getHour() << ":" << getMinute() << ":" << getSecond();
    }
};

constexpr int MAX_SIZE = 31;

class Lesson {
private:
    char room[MAX_SIZE + 1]{};
    Day day = Day::MONDAY;
    Subject subject = Subject::OOP;
    Time startTime = Time{};
    Time endTime = Time{};

public:
    void setRoom(const char *Room) {
        strcpy(this->room, Room);
    }

    const char *getRoom() const {
        return this->room;
    }

    Day getDay() const {
        return day;
    }

    void setDay(Day day) {
        this->day = day;
    }

    Subject getSubject() const {
        return subject;
    }

    void setSubject(Subject subject) {
        this->subject = subject;
    }

    Time getStartTime() const {
        return startTime;
    }

    void setStartTime(const Time &start_time) {
        startTime = start_time;
    }

    Time getEndTime() const {
        return endTime;
    }

    void setEndTime(const Time &end_time) {
        endTime = end_time;
    }

    void printLesson() const {
        cout << room << "; " << getDay() << "; " << subject << "; ";
        startTime.print();
        cout << " - ";
        endTime.print();
        // cout<<endl;
    }
};

class Schedule {
private:
    int sizeOfSchedule = 0;
    Lesson lessons[MAX_SIZE]{};

public:
    bool addNewSchedule(const char *Room, const Day Day,
                        const Subject Subject, const Time start, const Time end) {
        for (int i = 0; i < sizeOfSchedule; i++) {
            if (Day == lessons[i].getDay()) {
                if (strcmp(Room, lessons[i].getRoom()) == 0) {
                    if (!end.isBefore(lessons[i].getStartTime()) && // може и да трябва да се
                        !start.isAfter(lessons[i].getEndTime())) {
                        // сменят логическите връзки
                        cout << "This room isn't empty in this time slot." << endl;
                        return false;
                    }
                }
            }
        }
        lessons[sizeOfSchedule].setRoom(Room);
        lessons[sizeOfSchedule].setDay(Day);
        lessons[sizeOfSchedule].setSubject(Subject);
        lessons[sizeOfSchedule].setStartTime(start);
        lessons[sizeOfSchedule].setEndTime(end);
        sizeOfSchedule++;
        cout << "Added schedule" << endl;
        return true;
    }

    void filter(bool (*shouldFilter)(const Lesson &)) const {
        for (int i = 0; i < sizeOfSchedule; i++) {
            if (shouldFilter(lessons[i])) {
                lessons[i].printLesson();
                cout << endl;
            }
        }
    }
};

int main() {
    Schedule schedule;

    Time start1;
    start1.setHour(10);
    start1.setMinute(00);
    start1.setSecond(00);

    Time end1;
    end1.setHour(11);
    end1.setMinute(30);
    end1.setSecond(00);

    schedule.addNewSchedule(
        "301",
        Day::MONDAY,
        Subject::OOP,
        start1,
        end1
    );

    Time start2; // fail
    start2.setHour(11);
    start2.setMinute(00);
    start2.setSecond(00);

    Time end2;
    end2.setHour(13);
    end2.setMinute(00);
    end2.setSecond(00);

    schedule.addNewSchedule(
        "301",
        Day::MONDAY,
        Subject::DSTR2,
        start2,
        end2
    );

    cout << "Filter by room" << endl;
    schedule.filter([](const Lesson &lesson) { return strcmp(lesson.getRoom(), "301") == 0; });

    cout << "Filter by day" << endl;
    schedule.filter([](const Lesson &lesson) { return lesson.getDay() == Day::MONDAY; });

    return 0;
}
