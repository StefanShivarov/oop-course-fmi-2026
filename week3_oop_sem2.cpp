#include <iostream>
#include <cstring>
#include <print>
#include <format>

namespace utils {

    char* copyDynamicString(const char* src) {
        if (!src) {
            char* result = new char[1];
            result[0] = '\0';
            return result;
        }

        size_t len = strlen(src) + 1;
        char* result = new char[len];
        strcpy_s(result, len, src);
        return result;
    }
}

class Date {
private:
    int year = 1970;
    int month = 1;
    int day = 1;

    int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool isLeapYear(int y) const {
        return (y % 4 == 0) && (y % 100 != 0 || y % 400 == 0);
    }

    int getMaxDaysForMonth(int y, int m) const {
        if (m < 1 || m > 12) {
            return 0;
        }

        if (m == 2) {
            if (isLeapYear(y)) {
                return 29;
            }
            return 28;
        }

        return daysInMonth[m - 1];
    }

    bool isValidCombination(int y, int m, int d) const {
        if (y < 1900 || y > 2100) {
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
    Date() :Date(1970, 1, 1) {};

    Date(int y, int m, int d) {
        if (isValidCombination(y, m, d)) {
            year = y; month = m; day = d;
        }
    }

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

    void print() const {
        std::println("{}/{}/{}", day, month, year);
    }
};

class Student {
private:
    char* name = nullptr;
    int fn = 0;

public:
    Student() : Student("Unknown", 0) {

    }

    Student(const char* name, int fn) : fn(fn) {
        this->name = utils::copyDynamicString(name);
    }

    ~Student() {
        delete[] name;
        name = nullptr;
    }

    const char* getName() const {
        return name;
    }

    int getFn() const {
        return fn;
    }

    void setName(const char* newName) {
        delete[] name;
        name = utils::copyDynamicString(newName);
    }

    void setFn(int newFn) {
        if (newFn < 1000 || newFn > 9999) {
            return;
        }
        fn = newFn;
    }

    void print() const {
        std::println("Student: {} (fn: {})", name, fn);
    }
};

class Exam {
private:
    Date date;
    double grade;

public:
    Exam() : Exam(Date(), 2.0) {

    }

    Exam(Date d, double grade) :date(d), grade(grade) {

    }

    Date getDate()const {
        return date;
    }

    double getGrade()const {
        return grade;
    }

    void setDate(const Date& date) {
        this->date = date;
    }

    void setGrade(double grade) {
        this->grade = grade;
    }

    void print() const {
        std::println("Exam date: {}/{}/{} grade: {}",
            date.getDay(), date.getMonth(), date.getYear(), grade);
    }
};

class Results {
private:
    Student& s;                 //aggregation
    Exam* exams = nullptr;
    size_t count = 0;
    size_t capacity = 0;

public:
    
    Results(Student& student) : s(student) {
    
    }

    
    ~Results() {
        delete[] exams;
        exams = nullptr;
    }

    void createArray(int n) {
        delete[] exams;
        exams = new Exam[n];
        count = 0;
        capacity = n;
    }

    void print() const {
        s.print();
        for (int i = 0; i < count; i++)
            exams[i].print();
    }

    Exam getBestResult() const {

        if (count == 0) {
            return Exam();
        }

        Exam best = exams[0];
        for (int i = 1; i < count; i++) {
            if (exams[i].getGrade() > best.getGrade())
                best = exams[i];
        }
        return best;
    }

    double getAverage() const {
        if (count == 0) {
            return 0.0;
        }
        double sum = 0.0;
        for (int i = 0; i < count; i++) {
            sum += exams[i].getGrade();
        }
            
        return sum / count;
    }

    void resizeTheArray() {

        size_t newCap = (capacity == 0) ? 2 : capacity * 2;
        Exam* newArray = new Exam[newCap];

        for (size_t i = 0; i < count; i++) {
            newArray[i] = exams[i];
        }

        delete[] exams;
        exams = newArray;
        capacity = newCap;

    }

    void addResult(const Exam& e) {
        
        if (count >= capacity) {
            resizeTheArray();
        }

        exams[count] = e;
        count++;
    }

};

int main() {
    Student s("Ivan", 1234);
    Results r(s);

    r.addResult(Exam(Date(2026, 3, 7), 5.5));
    r.addResult(Exam(Date(2026, 3, 8), 6.0));
    r.addResult(Exam(Date(2026, 3, 9), 4.5));

    std::println("--- All results ---");
    r.print();

    std::println("\n--- Best result ---");
    r.getBestResult().print();

    std::println("\n--- Average ---\n{:.2f}", r.getAverage());
}
