#include <iostream>
#include <fstream>
#include <print>

using std::ostream;
using std::istream;
using std::cin;
using std::cout;
using std::println;
using std::swap;

namespace TimeUtils {
    class Time {
private:
    unsigned hours = 0;
    unsigned minutes = 0;
    unsigned seconds = 0;

    mutable bool validTotalSeconds = false;
    mutable unsigned totalSeconds = 0;

    void recalculate() {
        hours = totalSeconds / 3600;
        minutes = (totalSeconds % 3600) / 60;
        seconds = totalSeconds % 60;
        validTotalSeconds = true;
    }

public:
    unsigned toSeconds() const {
        if (validTotalSeconds) {
            return totalSeconds;
        }

        totalSeconds = seconds + minutes * 60 + hours * 3600;
        validTotalSeconds = true;
        return totalSeconds;
    }

    void addSeconds(int secondsDelta) {
        totalSeconds = this->toSeconds();
        totalSeconds += secondsDelta;
        recalculate();
    }

    bool isBefore(const Time& other) const {
        return this->toSeconds() < other.toSeconds();
    }

    bool isAfter(const Time& other) const {
        return this->toSeconds() > other.toSeconds();
    }

    unsigned getHours() const {
        return hours;
    }

    unsigned getMinutes() const {
        return minutes;
    }

    unsigned getSeconds() const {
        return seconds;
    }

    bool setHours(unsigned hours) {
        if (hours > 23) {
            return false;
        }
        this->hours = hours;
        validTotalSeconds = false;
        return true;
    }

    bool setMinutes(unsigned minutes) {
        if (minutes > 59) {
            return false;
        }
        this->minutes = minutes;
        validTotalSeconds = false;
        return true;
    }

    bool setSeconds(unsigned seconds) {
        if (seconds > 59) {
            return false;
        }
        this->seconds = seconds;
        validTotalSeconds = false;
        return true;
    }

};

    bool readTime(Time& time, istream& is = cin) {
        unsigned h, m, s;
        char delimiter;
        is >> h >> delimiter;
        if (!time.setHours(h) || delimiter != ':') {
            return false;
        }
        is >> m >> delimiter;
        if (!time.setMinutes(m) || delimiter != ':') {
            return false;
        }
        is >> s;
        return time.setSeconds(s);
    }

    void writeTime(const Time& time, ostream& os = cout) {
        print(os, "{:02}:{:02}:{:02}",
            time.getHours(), time.getMinutes(), time.getSeconds());
    }

    void sortTimes(Time* times, size_t timesCount, bool (*comparator) (const Time&, const Time&)) {
        for (int i = 0; i < timesCount; i++) {
            int minIndex = i;
            for (int j = i + 1; j < timesCount; j++) {
                if (comparator(times[j], times[minIndex])) {
                    minIndex = j;
                }
            }

            if (i != minIndex) {
                swap(times[i], times[minIndex]);
            }
        }
    }
}

namespace DaysUtils {
    enum class DayOfWeek {
        UNDEFINED,
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY
    };

    DayOfWeek getDayOfWeekFromString(unsigned day) {
        switch (day) {
            case 1: return DayOfWeek::MONDAY;
            case 2: return DayOfWeek::TUESDAY;
            case 3: return DayOfWeek::WEDNESDAY;
            case 4: return DayOfWeek::THURSDAY;
            case 5: return DayOfWeek::FRIDAY;
            default: return DayOfWeek::UNDEFINED;
        }
    }
}

namespace SubjectUtils {
    enum class Subject {
        UNDEFINED,
        OOP,
        DSTR,
        ALG,
        // ...
    };

    const char* convertSubjectToString(Subject subject) {
        switch (subject) {
            case Subject::OOP: return "OOP";
            case Subject::DSTR: return "DSTR";
            case Subject::ALG: return "ALG";
                // ...
            default: return "Undefined";
        }
    }

    Subject getSubjectFromString(const char* str) {
        if (strcmp(str, "OOP") == 0) {
            return Subject::OOP;
        }
        if (strcmp(str, "DSTR") == 0) {
            return Subject::DSTR;
        }
        if (strcmp(str, "ALG") == 0) {
            return Subject::ALG;
        }
        return Subject::UNDEFINED;
    }
}

using namespace TimeUtils;
using namespace DaysUtils;
using namespace SubjectUtils;

namespace LessonUtils {
    class Lesson {
    private:
        unsigned room = 0;
        DayOfWeek day = DayOfWeek::UNDEFINED;
        Subject subject = Subject::UNDEFINED;
        Time startTime;
        Time endTime;

    public:
        bool overlapsWith(const Lesson& other) const {
            if (day != other.day || room != other.room) {
                return false;
            }
            return this->startTime.toSeconds() < other.endTime.toSeconds()
                && other.startTime.toSeconds() < this->endTime.toSeconds();
        }

        unsigned getRoom() const {
            return room;
        }

        DayOfWeek getDayOfWeek() const {
            return day;
        }

        Subject getSubject() const {
            return subject;
        }

        const Time& getStartTime() const {
            return startTime;
        }

        const Time& getEndTime() const {
            return endTime;
        }

        void setStartTime(const Time& time) {
            this->startTime = time;
        }

        void setEndTime(const Time& time) {
            this->endTime = time;
        }

        bool isValid() const {
            return day != DayOfWeek::UNDEFINED
                && subject != Subject::UNDEFINED
                && startTime.isBefore(endTime);
        }

        void setSubject(const Subject& subject) {
            this->subject = subject;
        }

        void setDayOfWeek(DayOfWeek day) {
            this->day = day;
        }

        void setRoom(unsigned room) {
            this->room = room;
        }
    };

    void writeLesson(const Lesson& lesson, ostream& os = cout) {
        print(os, "{},{},{},",
                        (int) lesson.getDayOfWeek(),
                        lesson.getRoom(),
                        convertSubjectToString(lesson.getSubject()));

        writeTime(lesson.getStartTime(), os);
        os << ',';
        writeTime(lesson.getEndTime(), os);
        os << '\n';
    }

    void readLesson(Lesson& lesson, istream& is = cin) {
        // you can make this function return bool
        char delimiter;
        unsigned day;
        is >> day;
        lesson.setDayOfWeek(getDayOfWeekFromString(day));
        is >> delimiter;

        unsigned room;
        is >> room;
        lesson.setRoom(room);
        is >> delimiter;

        char subject[100];
        is.getline(subject, 100, ',');
        lesson.setSubject(getSubjectFromString(subject));

        Time time;
        readTime(time, is);
        lesson.setStartTime(time);
        is >> delimiter;

        readTime(time, is);
        lesson.setEndTime(time);
    }
}

using namespace LessonUtils;

class Schedule {
private:
    Lesson lessons[50];
    size_t lessonsCount = 0;

    bool hasConflict(const Lesson& lesson) const {
        for (size_t i = 0; i < lessonsCount; i++) {
            if (lessons[i].overlapsWith(lesson)) {
                return true;
            }
        }
        return false;
    }

public:
    size_t getLessonsCount() const {
        return lessonsCount;
    }

    bool addLesson(const Lesson& lesson) {
        if (lessonsCount == 50) {
            return false;
        }
        if (!lesson.isValid()) {
            return false;
        }
        if (hasConflict(lesson)) {
            return false;
        }
        lessons[lessonsCount++] = lesson;
        return true;
    }

    void writeAllLessons(ostream& os = cout) const {
        for (size_t i = 0; i < lessonsCount; i++) {
            writeLesson(lessons[i], os);
        }
    }

    void filterLessons(bool (*shouldFilter)(const Lesson&), ostream& os = cout) const {
        for (size_t i = 0; i < lessonsCount; i++) {
            if (shouldFilter(lessons[i])) {
                writeLesson(lessons[i], os);
            }
        }
    }

    void readAllLessons(istream& is = cin) {
        // you can make this function return bool
        unsigned count;
        is >> count;
        for (int i = 0; i < count; i++) {
            Lesson lesson;
            readLesson(lesson, is);
            addLesson(lesson);
        }
    }

    bool saveToFile(const char* fileName) const {
        std::ofstream ofs(fileName);
        if (!ofs.is_open()) {
            return false;
        }

        ofs << lessonsCount << '\n';
        writeAllLessons(ofs);
        return true;
    }

    bool loadFromFile(const char* fileName) {
        std::ifstream ifs(fileName);
        if (!ifs.is_open()) {
            return false;
        }

        readAllLessons(ifs);
        return true;
    }
};

int main(){
    Schedule schedule;
    schedule.loadFromFile("schedule.txt");
    cout << "All lessons: \n";
    schedule.writeAllLessons();
    cout << "Filtered lessons by Monday:\n";
    schedule.filterLessons([](const Lesson& lesson) {
        return lesson.getDayOfWeek() == DayOfWeek::MONDAY;
    });
    cout << "Filtered lessons by room 325:\n";
    schedule.filterLessons([](const Lesson& lesson) {
        return lesson.getRoom() == 325;
    });
}
