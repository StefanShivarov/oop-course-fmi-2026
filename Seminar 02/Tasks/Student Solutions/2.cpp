#include <iostream>
const int MAX_SIZE = 32;
const int MAX_LESSONS = 32;
const int TIME_ARR_SIZE = 9;
const int MAX_TIMES = 20;
const int MAX_SECONDS = 59;
const int MAX_MINUTES = 59;
const int MAX_HOUR = 23;
const int NUMBER_OF_SECONDS_IN_AN_HOUR = 3600;
const int NUMBER_OF_SECONDS_IN_A_MINUTE = 60;
const int NUMBER_OF_MINUTES_IN_AN_HOUR = 60;

bool areTheSameStr(const char *p, const char *s)
{
    int countr = 0;
    while (*(p + countr) != '\0')
    {
        if (*(p + countr) != *(s + countr))
            return false;
        countr++;
    }
    return *(s + countr) == '\0';
}

bool isValid(int a, int max)
{
    return (a >= 0 && a <= max);
}

void copyStr(char *dest, const char *src)
{
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

bool isValidInput(const char *arr)
{
    if (arr[0] > '2' || arr[0] < '0')
        return false;
    if (arr[1] > '9' || arr[1] < '0')
        return false;
    if (arr[1] > '3' && arr[0] == '2')
        return false;

    if (arr[2] != ':' || arr[5] != ':')
        return false;

    if (arr[3] > '5' || arr[3] < '0')
        return false;
    if (arr[4] > '9' || arr[4] < '0')
        return false;
    if (arr[6] > '5' || arr[6] < '0')
        return false;
    if (arr[7] > '9' || arr[7] < '0')
        return false;
    return true;
}

bool isOneDigit(int a)
{
    return isValid(a, 9);
}

void invalidInput()
{
    std::cout << "\nInvalid input.";
}

class Time
{
private:
    int hour;
    int minutes;
    int seconds;

public:
    void printTime() const
    {
        std::cout << "\nTime: ";
        if (isOneDigit(this->hour))
        {
            std::cout << "0";
        }
        std::cout << this->hour << ":";
        if (isOneDigit(this->minutes))
        {
            std::cout << "0";
        }
        std::cout << this->minutes << ":";
        if (isOneDigit(this->seconds))
        {
            std::cout << "0";
        }
        std::cout << this->seconds;
    }

    void setSeconds(int seconds)
    {
        if (isValid(seconds, MAX_SECONDS))
        {
            this->seconds = seconds;
        }
        else
        {
            invalidInput();
        }
    }
    void setMinutes(int minutes)
    {
        if (isValid(minutes, MAX_MINUTES))
        {
            this->minutes = minutes;
        }
        else
        {
            invalidInput();
        }
    }
    void setHour(int hour)
    {
        if (isValid(hour, MAX_HOUR))
        {
            this->hour = hour;
        }
        else
        {
            invalidInput();
        }
    }
    void setTime(int hour, int minutes, int seconds)
    {
        if (isValid(seconds, MAX_SECONDS) &&
            isValid(minutes, MAX_MINUTES) &&
            isValid(hour, MAX_HOUR))
        {
            this->hour = hour;
            this->minutes = minutes;
            this->seconds = seconds;
        }
        else
        {
            invalidInput();
        }
    }

    int toSeconds() const
    {
        return this->hour * NUMBER_OF_SECONDS_IN_AN_HOUR + this->minutes * NUMBER_OF_SECONDS_IN_A_MINUTE + this->seconds;
    }

    void addSeconds(int delta)
    {
        int deltaSeconds = delta % NUMBER_OF_SECONDS_IN_A_MINUTE;
        int deltaMinutes = (delta / NUMBER_OF_SECONDS_IN_A_MINUTE) % NUMBER_OF_SECONDS_IN_A_MINUTE;
        int deltaHours = delta / NUMBER_OF_SECONDS_IN_AN_HOUR;

        int additionalMinutes = (this->seconds + deltaSeconds) / NUMBER_OF_SECONDS_IN_A_MINUTE;
        int additionalHours = (this->minutes + deltaMinutes + additionalMinutes) / NUMBER_OF_MINUTES_IN_AN_HOUR;
        this->seconds = (this->seconds + deltaSeconds) % (MAX_SECONDS + 1);
        this->minutes = (this->minutes + deltaMinutes + additionalMinutes) % (MAX_MINUTES + 1);
        this->hour = (this->hour + deltaHours + additionalHours) % (MAX_HOUR + 1);
    }
    bool sameTimeAsOther(const Time &other) const
    {
        return this->toSeconds() == other.toSeconds();
    }
    bool isBefore(const Time &other) const
    {
        return this->toSeconds() < other.toSeconds();
    }

    bool isAfter(const Time &other) const
    {
        return this->toSeconds() > other.toSeconds();
    }
};

enum class WeekDays
{
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

void printDay(WeekDays day)
{
    switch (day)
    {
    case WeekDays::Monday:
        std::cout << "Monday";
        break;
    case WeekDays::Tuesday:
        std::cout << "Tuesday";
        break;
    case WeekDays::Wednesday:
        std::cout << "Wednesday";
        break;
    case WeekDays::Thursday:
        std::cout << "Thursday";
        break;
    case WeekDays::Friday:
        std::cout << "Friday";
        break;
    case WeekDays::Saturday:
        std::cout << "Saturday";
        break;
    default:
        std::cout << "Sunday";
        break;
    }
}
enum class Subject
{
    OOP,
    DSTR2,
    GEOMETRY,
    DIS,
    ENGLISH,
    Complex_Analysis
};
void printSubject(Subject subject)
{
    switch (subject)
    {
    case Subject::OOP:
        std::cout << "OOP";
        break;
    case Subject::DSTR2:
        std::cout << "DSTR2";
        break;
    case Subject::GEOMETRY:
        std::cout << "GEOMETRY";
        break;
    case Subject::DIS:
        std::cout << "DIS";
        break;
    case Subject::ENGLISH:
        std::cout << "ENGLISH";
        break;
    default:
        std::cout << "Complex Analysis";
        break;
    }
}
class Lesson
{
private:
    char room[MAX_SIZE];
    WeekDays day;
    Subject subject;
    Time startTime;
    Time endTime;

public:
    void setRoom(const char *room)
    {
        copyStr(this->room, room);
    }
    const char *getRoom() const
    {
        return room;
    }
    void setDay(WeekDays d)
    {
        day = d;
    }
    WeekDays getDay() const
    {
        return day;
    }

    void setSubject(Subject s)
    {
        subject = s;
    }
    Subject getSubject() const
    {
        return subject;
    }
    void setStartTime(const Time &t)
    {
        startTime = t;
    }
    Time getStartTime() const
    {
        return startTime;
    }

    void setEndTime(const Time &t)
    {
        endTime = t;
    }
    Time getEndTime() const
    {
        return endTime;
    }
    void addNewLesson(char *room, WeekDays weekday, Subject subject, Time const startTime, Time const endTime)
    {
        copyStr(this->room, room);
        this->day = weekday;
        this->subject = subject;
        this->startTime = startTime;
        this->endTime = endTime;
    }
    void printLesson() const
    {
        std::cout << "\nSubject: ";
        printSubject(this->subject);
        std::cout << "\nRoom: " << this->room;
        std::cout << "\nWeekday: ";
        printDay(this->day);
        std::cout << "\nStart: ";
        this->startTime.printTime();
        std::cout << "\nEnd: ";
        this->endTime.printTime();
    }
};

bool isPossibleToAdd(const Lesson &lesson, int lessonCount, const Lesson* lessons)
{
    for (int i = 0; i < lessonCount; i++)
    {
        if (lessons[i].getDay() == lesson.getDay() &&
            areTheSameStr(lessons[i].getRoom(), lesson.getRoom()))
        {
            Time start1 = lessons[i].getStartTime();
            Time end1 = lessons[i].getEndTime();
            Time start2 = lesson.getStartTime();
            Time end2 = lesson.getEndTime();
            if (!(end1.isBefore(start2) || end2.isBefore(start1)))
                return false;
        }
    }
    return true;
}


class Schedule
{
private:
    Lesson lessons[MAX_LESSONS];
    int lessonCount;

public:
    void resetLessonCount()
    {
        this->lessonCount = 0;
    }
    void addLesson(const Lesson &lesson)
    {
        if (!isPossibleToAdd(lesson, this->lessonCount, lessons))
        {
            return;
        }
        this->lessonCount++;
        this->lessons[lessonCount - 1] = lesson;
    }
    void printByDay(WeekDays day) const
    {
        for (int i = 0; i < this->lessonCount; i++)
        {
            if (this->lessons[i].getDay() == day)
            {
                this->lessons[i].printLesson();
            }
        }
    }
    void printByRoom(const char *room) const
    {
        for (int i = 0; i < this->lessonCount; i++)
        {
            if (areTheSameStr(this->lessons[i].getRoom(), room))
            {
                this->lessons[i].printLesson();
            }
        }
    }
};
int main()
{
    Schedule schedule;
    schedule.resetLessonCount();
    Lesson arr[MAX_SIZE];
    int n;
    Time t1, t2;
    t1.setHour(10);
    t1.setMinutes(10);
    t1.setSeconds(20);
    t2.setHour(11);
    t2.setMinutes(2);
    t2.setSeconds(3);
    std::cout << "\nHow many lessons to enter: ";
    std::cin >> n;
    arr[0].addNewLesson("325", WeekDays::Saturday, Subject::DSTR2, t1, t2);
    arr[1].addNewLesson("200", WeekDays::Tuesday, Subject::DIS, t1, t2);
    arr[2].addNewLesson("101", WeekDays::Wednesday, Subject::GEOMETRY, t1, t2);
    for (int i = 0; i < n; i++)
    {
        schedule.addLesson(arr[i]);
    }
    schedule.printByRoom("325");
    schedule.printByDay(WeekDays::Wednesday);
}