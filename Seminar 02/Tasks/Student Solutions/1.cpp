#include <iostream>
#include <fstream>
const int TIME_ARR_SIZE = 9;
const int MAX_TIMES = 20;
const int MAX_SECONDS = 59;
const int MAX_MINUTES = 59;
const int MAX_HOUR = 23;
const int NUMBER_OF_SECONDS_IN_AN_HOUR = 3600;
const int NUMBER_OF_SECONDS_IN_A_MINUTE = 60;
const int NUMBER_OF_MINUTES_IN_AN_HOUR = 60;

int fromCharToInt(char s)
{
    if (s >= '0' && s <= '9')
        return s - '0';
    else
        return -1;
}

bool isValid(int a, int max)
{
    return (a >= 0 && a <= max);
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
    int getHour() const
    {
        return this->hour;
    }
    int getMinutes() const
    {
        return this->minutes;
    }
    int getSeconds() const
    {
        return this->seconds;
    }
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
Time convert(const char *p)
{
    Time result = {};
    result.setHour(fromCharToInt(p[0]) * 10 + fromCharToInt(p[1]));
    result.setMinutes(fromCharToInt((p[3])) * 10 + fromCharToInt(p[4]));
    result.setSeconds(fromCharToInt(p[6]) * 10 + fromCharToInt(p[7]));
    return result;
}

void swap(Time &t1, Time &t2)
{
    Time temp = t1;
    t1 = t2;
    t2 = temp;
}

void sortTimes(Time arr[MAX_TIMES], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].toSeconds() > arr[j + 1].toSeconds())
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void printTimes(Time arr[MAX_TIMES], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i].printTime();
    }
}

void writeToFile(Time *times, int n, std::ofstream &file)
{
    for (int i = 0; i < n; i++)
    {
        if(isOneDigit(times[i].getHour())) file<<"0";
        file << times[i].getHour() << ":";
        if(isOneDigit(times[i].getMinutes())) file<<"0";
        file<<times[i].getMinutes() << ":";
        if(isOneDigit(times[i].getSeconds())) file<<"0";
        file<<times[i].getSeconds() << "\n";
    }
}

int main()
{
    int n;
    std::cout << "\nHow many time inputs? ";
    std::cin >> n;
    std::ifstream file("times.txt");
    std::ofstream fileOut("timesOut.txt");
    if (!file)
    {
        std::cerr << "\nError when reading file.";
        return -1;
    }
        if (!fileOut)
    {
        std::cerr << "\nError when writing file.";
        return -1;
    }
    char arr[MAX_TIMES][TIME_ARR_SIZE];
    Time times[MAX_TIMES];
    for (int i = 0; i < n; i++)
    {
        file >> arr[i];
        if(isValidInput(arr[i])){
        times[i] = convert(arr[i]);
        }else {
            i--;
        }
    }
    Time t;
    t.setHour(10);
    t.setMinutes(10);
    t.setSeconds(20);
    sortTimes(times, n);
    printTimes(times, n);
    writeToFile(times, n, fileOut);
    file.close();
    fileOut.close();
}