#include <iostream>
#include <fstream>
#include <cstring>
#include "task1.h"
using std::cin;
using std::cout;
using std::endl;

enum class DayOfTheWeek {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
};

enum class NameOfClass {
    OOP,
    DSTR2,
    DIS2,
    GEOMETRY
};

class Schedule {
    private: 
        char hallName[31];
        DayOfTheWeek day;
        NameOfClass nameOfClass;
        Time startingTime;
        Time endingTime;
    public:
        void getHallName(char* hallName) const {
            strcpy(hallName, this->hallName);
        }
        void getDay(DayOfTheWeek& day) const {
            day = this->day;
        }
        void getNameOfClass(NameOfClass& nameOfClass) const {
            nameOfClass = this->nameOfClass;
        }
        void getStartingTime(Time& startingTime) const {
            startingTime = this->startingTime;
        }
        void getEndingTime(Time& endingTime) const {
            endingTime = this->endingTime;
        }

        void setHallName(const char* hallName) {
            strcpy(this->hallName, hallName);
        }
        void setDay(DayOfTheWeek day) {
            this->day = day;
        }
        void setNameOfClass(NameOfClass nameOfClass) {
            this->nameOfClass = nameOfClass;
        }
        void setStartingTime(const Time& startingTime) {
            this->startingTime = startingTime;
        }
        void setEndingTime(const Time& endingTime) {
            this->endingTime = endingTime;
        }

        void readSchedule(std::istream& in) {
            char hallName[31];
            int dayInt;
            int nameOfClassInt;
            Time startingTime;
            Time endingTime;
            cout << "\nenter schedule in format: hallName, day, nameOfClass, startingTime, endingTime" << endl;
            cout << "the day and nameOfClass should be entered as a number, where: " << endl;
            cout << "0 - MONDAY, 1 - TUESDAY, 2 - WEDNESDAY, 3 - THURSDAY, 4 - FRIDAY" << endl;
            cout << "0 - OOP, 1 - DSTR2, 2 - DIS2, 3 - GEOMETRY" << endl;
            in >> hallName >> dayInt >> nameOfClassInt;
            cout << "enter starting time in format HH:MM:SS: ";
            startingTime.readTime(in);
            cout << "enter ending time in format HH:MM:SS: ";
            endingTime.readTime(in);
            setHallName(hallName);
            setDay(static_cast<DayOfTheWeek>(dayInt));
            setNameOfClass(static_cast<NameOfClass>(nameOfClassInt));
            setStartingTime(startingTime);
            setEndingTime(endingTime);
        }

        bool validAdd(DayOfTheWeek otherDay, char* otherHallName, const Time& otherStartingTime, const Time& otherEndingTime) const {
            if (day != otherDay || strcmp(hallName, otherHallName) != 0) {
                return true;
            }
            if (startingTime.isBefore(otherStartingTime) && endingTime.isBefore(otherStartingTime)) {
                return true;
            }
            if (startingTime.isAfter(otherEndingTime) && endingTime.isAfter(otherEndingTime)) {
                return true;
            }
            return false;
        }

        bool addSchedule(std::ostream& out, const Schedule& schedule) const {
            char hallName[31];
            DayOfTheWeek day;
            NameOfClass nameOfClass;
            Time startingTime;
            Time endingTime;
            schedule.getHallName(hallName);
            schedule.getDay(day);
            schedule.getNameOfClass(nameOfClass);
            schedule.getStartingTime(startingTime);
            schedule.getEndingTime(endingTime);
            if (!validAdd(day, hallName, startingTime, endingTime)) {
                return false;
            }
            out << hallName << " " << static_cast<int>(day) << " " << static_cast<int>(nameOfClass) << " ";
            startingTime.writeTime(out);
            out << " ";
            endingTime.writeTime(out);
            return true;
        }

        void filterByDay(std::ostream& out, const Schedule* schedules, DayOfTheWeek day, int n) const {
            for (int i = 0; i < n; i++) {
                char hallName[31];
                DayOfTheWeek scheduleDay;
                NameOfClass nameOfClass;
                Time startingTime;
                Time endingTime;

                schedules[i].getHallName(hallName);
                schedules[i].getDay(scheduleDay);
                schedules[i].getNameOfClass(nameOfClass);
                schedules[i].getStartingTime(startingTime);
                schedules[i].getEndingTime(endingTime);

                if (scheduleDay == day) {
                    out << hallName << " " << static_cast<int>(scheduleDay) << " " << static_cast<int>(nameOfClass) << " ";
                    startingTime.writeTime(out);
                    out << " ";
                    endingTime.writeTime(out);
                    out << endl;
                }
            }
        }
        void filterByDay(std::ostream& out, const Schedule* schedules, char* otherHallName, int n) const {
            for (int i = 0; i < n; i++) {
                char hallName[31];
                DayOfTheWeek scheduleDay;
                NameOfClass nameOfClass;
                Time startingTime;
                Time endingTime;

                schedules[i].getHallName(hallName);
                schedules[i].getDay(scheduleDay);
                schedules[i].getNameOfClass(nameOfClass);
                schedules[i].getStartingTime(startingTime);
                schedules[i].getEndingTime(endingTime);
                
                if (strcmp(hallName, otherHallName) == 0) {
                    out << hallName << " " << static_cast<int>(scheduleDay) << " " << static_cast<int>(nameOfClass) << " ";
                    startingTime.writeTime(out);
                    out << " ";
                    endingTime.writeTime(out);
                    out << endl;
                }
            }
        }
    
    void readFromStream(std::istream& in) {
        char hall[31];
        int dayInt, classInt;
        Time start, end;

        in >> hall >> dayInt >> classInt;
        start.readTime(in);
        end.readTime(in);

        setHallName(hall);
        setDay(static_cast<DayOfTheWeek>(dayInt));
        setNameOfClass(static_cast<NameOfClass>(classInt));
        setStartingTime(start);
        setEndingTime(end);
    }

    void writeToStream(std::ostream& out) const {
        out << hallName << " " << static_cast<int>(day) << " " << static_cast<int>(nameOfClass) << " ";
        startingTime.writeTime(out);
        out << " ";
        endingTime.writeTime(out);
        out << "\n";
    }
};

int main() {
    int n;
    cout << "enter number of schedules to add: ";
    cin >> n;
    Schedule* schedules = new Schedule[n];

    for (int i = 0; i < n; i++) {
        schedules[i].readSchedule(cin);
    }

    for (int i = 0; i < n; i++) {
        schedules[i].addSchedule(cout, schedules[i]);
    }

    cout << "\nenter a day to filter by: ";
    int dayInt;
    cin >> dayInt;
    cout << "\nschedules for that day: " << endl;
    schedules[0].filterByDay(cout, schedules, static_cast<DayOfTheWeek>(dayInt), n);    
    cout << "\nenter a hall name to filter by: ";
    char hallName[31];
    cin >> hallName;
    cout << "\nschedules for that hall: " << endl;
    schedules[0].filterByDay(cout, schedules, hallName, n);

    std::ofstream fout("schedule.txt");
    for (int i = 0; i < n; ++i) {
        schedules[i].writeToStream(fout);
    }
    fout.close();

    std::ifstream fin("schedule.txt");
    for (int i = 0; i < n; ++i) {
        schedules[i].readFromStream(fin);
    }
    fin.close();

    delete[] schedules;
}


