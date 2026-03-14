#include <iostream>
#include <print> 

using std::println;
using std::print;
using std::cin;

class Date {
    int day;
    int month;
    int year;

    bool isLeapYear(int y) const
    {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    int daysInMonth(int m, int y) const
    {
        switch (m)
        {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return isLeapYear(y) ? 29 : 28;
        default: return 0;
        }
    }

    bool isValidDate(int d, int m, int y) const
    {
        if (y < 2000 || y > 2026)
        {
            return false;
        }
        if (m < 1 || m > 12)
        {
            return false;
        }

        int maxDays = daysInMonth(m, y);
        if (d < 1 || d > maxDays)
        {
            return false;
        }

        return true;
    }

public:
    Date() : day(1), month(1), year(2000) {}

    Date(int d, int m, int y)
    {
        if (!setDate(d, m, y))
        {
            this->day = 1;
            this->month = 1;
            this->year = 2000;
            //default date
        }
    }

    bool setDate(int d, int m, int y)
    {
        if (!isValidDate(d, m, y))
        {
            return false;
        }

        day = d;
        month = m;
        year = y;
        return true;
    }

    void printDate() const
    {
        println("Date:{:02}.{:02}.{}", day, month, year);
    }
};

class ExamResult
{
    int grade;
    Date date;

public:
    ExamResult() : grade(0), date() {}

    ExamResult(int g, const Date& d) : grade(g), date(d) {}

    int getGrade() const
    {
        return grade;
    }

    void print() const
    {
        println("Grade:{} ", grade);
        date.printDate();
        println();
    }
};

class StudentExams
{
    ExamResult* results;
    size_t count;
    size_t capacity;

    void resizeTheArray()
    {
        size_t newCapacity = capacity == 0 ? 1 : 2 * capacity;

        ExamResult* newArray = new ExamResult[newCapacity];
        for (size_t i = 0; i < count; i++)
        {
            newArray[i] = results[i];
        }

        delete[] results;
        results = newArray;
        capacity = newCapacity;
    }

public:
    StudentExams() = default;

    StudentExams(size_t initialCapacity): count(0), capacity(initialCapacity) 
    {
        results = new ExamResult[initialCapacity];
    }

    ~StudentExams()
    {
        delete[] results;
    }

    void addResult(const ExamResult& r)
    {
        if (count >= capacity)
        {
            resizeTheArray();
        }

        results[count++] = r;
    }

    void printAll() const
    {
        println("Student's Exam Results:");
        for (size_t i = 0; i < count; i++)
        {
            results[i].print();
        }
    }

    ExamResult getBestResult() const
    {
        if (count == 0)
        {
            return ExamResult();
        }

        ExamResult best = results[0];
        for (size_t i = 1; i < count; i++)
        {
            if (results[i].getGrade() > best.getGrade())
            {
                best = results[i];
            }
        }

        return best;
    }

    double getAverage() const
    {
        if (count == 0)
        {
            return 0;
        }

        double sum = 0;
        for (size_t i = 0; i < count; i++)
        {
            sum += results[i].getGrade();
        }
        return sum / count;
    }
};

int main()
{
    size_t inputCapacity;
    println("Enter capacity for the exams:");
    cin >> inputCapacity;

    StudentExams exams(inputCapacity);

    Date d1(31, 2, 2026);
    Date d2(26, 4, 2026);
    Date d3(27, 3, 2026);

    exams.addResult(ExamResult(5, d1));
    exams.addResult(ExamResult(6, d2));
    exams.addResult(ExamResult(4, d3));

    exams.printAll();

    println("Best Result:");
    exams.getBestResult().print();

    println("Average Grade: {:.2f}", exams.getAverage());

    Date d4(25, 5, 2026);
    exams.addResult(ExamResult(6, d4));

    println("\nAfter adding a new exam:");
    exams.printAll();

    println("\nBest Result:");
    exams.getBestResult().print();

    println("Average Grade: {:.2f}", exams.getAverage());

    return 0;
}