#include <iostream>
#include <print>
#include <format>
#include <cstring>
#pragma warning(disable : 4996) // za strcpy

using std::cin;
using std::cout;
using std::println;

class Date {
private:
    int day = 1;
    int month = 1;
    int year = 2000;


    bool isLeapYear(int y) const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    int daysInMonth(int m, int y) const {
        if (m == 2) {
            if (isLeapYear(y)) {
                return 29;
            }
            else {
                return 28;
            }
        }

        if (m == 4 || m == 6 || m == 9 || m == 11)
            return 30;

        return 31;
    }

    bool isValidDate(int d, int m, int y) const {
        if (y <= 0) return false;
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > daysInMonth(m, y)) return false;
        return true;
    }

public:
    Date(int day = 1, int month = 1, int year = 2000) {
        if (isValidDate(day, month, year)) {
            this->day = day;
            this->month = month;
            this->year = year;
        }
    }

    void printDate() const {
        println("Date: {:02}.{:02}.{}", day, month, year);
    }
};

enum class Subject {
    OOP, GEOMETRY, DSTR2, DIS2
};

const char* toString(const Subject& s) {
    switch (s) {
    case Subject::OOP: return "OOP";
    case Subject::GEOMETRY: return "GEOMETRY";
    case Subject::DSTR2: return "DSTR2";
    case Subject::DIS2: return "DIS2";
    default:
        return "other";
    }
}

class Exam {
private:
    Subject subject;
    double grade;
    Date date;

public:
    Exam() :grade(0.0) { };
    Exam(double grade, const Date& date, const Subject& subject) : date(date), subject(subject) {
        setGrade(grade);
    }

    double getGrade() const {
        return grade;
    }

    Date getDate() const {
        return date;
    }

    Subject getSubject() const {
        return subject;
    }

    void setGrade(double newGrade) {
        if (newGrade >= 2.0 && newGrade <= 6.0) {
            grade = newGrade;
        }
        else {
            grade = 2.0;
        }
    }

    void setDate(const Date& newDate) {
        this->date = newDate;
    }

    void setSubject(Subject newSub) {
        subject = newSub;
    }

    void printExamInfo() const {
        date.printDate();
        println("Subject: {}, Grade: {}", toString(subject), grade);
        println(" ");
    }
};

class AllExams {
private:
    Exam* exams = nullptr;
    int count = 0;
    int capacity = 0;

    void resize() {
        capacity *= 2;
        Exam* temp = new Exam[capacity];

        for (int i = 0; i < count; i++)
        {
            temp[i] = exams[i];
        }

        delete[]exams;
        exams = temp;
    }

public:
    AllExams() {
        count = 0;
        capacity = 2;
        exams = new Exam[capacity];
    }

    ~AllExams() {
        delete[]exams;
        exams = nullptr;
    }

    void printExams() const {
        for (int i = 0; i < count; i++)
        {
            exams[i].printExamInfo();
        }
    }

    double getBestResult() const {
        double best = exams[0].getGrade();
        for (int i = 1; i < count; i++)
        {
            if (best < exams[i].getGrade()) {
                best = exams[i].getGrade();
            }
        }

        return best;
    }

    double getAvgResult() const {
        double sum = 0;
        for (int i = 0; i < count; i++)
        {
            sum+= exams[i].getGrade();
        }

        return sum / count;
    }

    void addResult(const Exam& newExam) {
        if (count == capacity) {
            resize();
        }

        exams[count] = newExam;
        count++;
    }
};

int main() {
    AllExams myExams;

    Date d1(01, 04, 2026);
    Exam exam1(4.7, d1, Subject::OOP);

    Date d2(12, 04, 2026);
    Exam exam2(3, d2, Subject::GEOMETRY);

    Date d3(22, 05, 2026);
    Exam exam3(4.2, d3, Subject::DIS2);

    Date d4(04, 06, 2026);
    Exam exam4(5.95, d4, Subject::DSTR2);


    myExams.addResult(exam1);
    myExams.addResult(exam2);
    myExams.addResult(exam3);
    myExams.addResult(exam4);

    println("The average result is {:.2f}", myExams.getAvgResult());

    println("The best result is {:.2f}", myExams.getBestResult());

    cout << '\n';

    println("--- My Exams Information ---");
    myExams.printExams();
}