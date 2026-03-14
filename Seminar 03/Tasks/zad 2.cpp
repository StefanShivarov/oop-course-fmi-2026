#include <iostream>
using std::cout;
using std::endl;

class Date {
private:
    int year = 1970;
    int month = 1;
    int day = 1;
    int DAYS_IN_MONTH[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool isLeapYear(int y) const {
        return (y % 4 == 0) && (y % 100 != 0 || y % 400 == 0);
    }
    int getMaxDaysForMonth(int y, int m) const {
        if (m < 1 || m > 12) {
            return 0;
        }

        if (m == 2 && isLeapYear(y)) {
            return 29;
        }

        return DAYS_IN_MONTH[m - 1];
    }
    bool isValidCombination(int y, int m, int d) const {
        if (y < 1) {
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
    Date() {}  

    Date(int y, int m, int d) {
        setAll(y, m, d);
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
        cout << day << "." << month << "." << year;
    }
};


struct ExamResult {

    double grade = 2.0;
    Date date;

    ExamResult() {}
    ExamResult(double grade, const Date& date) : grade(grade), date(date) {}
};


class StudentExams {
private:
    ExamResult* results = nullptr;
    int size = 0;
    int capacity = 0;

    void resize() {
        capacity *=2;
        ExamResult* newArr = new ExamResult[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = results[i];
        }
        delete[] results;
        results = newArr;
    }

public:
    StudentExams() : StudentExams(20) {}

    StudentExams(int capacity) : size(0), capacity(capacity) {
        results = new ExamResult[capacity];
    }

    ~StudentExams() {
        delete[] results;
        results = nullptr;
        size = 0;
        capacity = 0;
    }

    int getSize() const { 
        return size; 
    }
    int getCapacity() const{ 
        return capacity;
    }

    void addResult(double grade, const Date& date) {
        if (size == capacity) {
            resize();
        }
        results[size++] = ExamResult(grade, date);
    }

    double getMax() const {
        if (size == 0) {
            return 0;
        }
        double max = results[0].grade;
        for (int i = 1; i < size; i++) {
            if (results[i].grade > max)
            {
                max = results[i].grade;
            }
        }
        return max;
    }

    double getAverage() const {
        if (size == 0) {
            return 0;
        }
        double sum = 0;
        for (int i = 0; i < size; i++)
        {
            sum += results[i].grade;
        }
        return sum / size;
    }

    void printAll() const {
        for (int i = 0; i < size; i++) {
            cout << "  Exam " << (i + 1) << ": grade = " << results[i].grade << ", date = ";
            results[i].date.print();
            cout << endl;
        }
    }
};

int main() {

    StudentExams student(2);  

    student.addResult(5.50, Date(2026, 2, 18));
    student.addResult(4.75, Date(2026, 3, 15));
    student.addResult(6.00, Date(2026, 5, 20));  

    cout << "All results:" << endl;
    student.printAll();
    cout << endl;

    cout << "Best: " << student.getMax() << endl;
    cout << "Average: " << student.getAverage() << endl;
}