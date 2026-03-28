#include <iostream>
#include <print>

using std::cout;
using std::endl;
using std::ostream;

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
    Date() = default;

    Date(int day, int month, int year) {
        if (isValidCombination(year, month, day)) {
            this->year = year;
            this->month = month;
            this->day = day;
        }
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
};

void printDate(const Date &date, ostream& os = cout) {
    std::print(os, "{:02}/{:02}/{:04}", date.getDay(), date.getMonth(), date.getYear());
}

class ExamResult {
private:
    double result = 0.0;
    double pointsTotal = 1.0;
    Date date;

public:
    ExamResult() = default;

    ExamResult(double result, double limit, const Date& date) : date(date) {
        setResult(result);
        setPointsTotal(limit);
    }

    double getResult() const {
        return result;
    }

    double getGrade() const {
        return (result / pointsTotal) * 100;
    }

    const Date& getDate() const {
        return date;
    }

    bool setResult(double points) {
        if (points < 0.0 || points > pointsTotal) {
            return false;
        }
        this->result = points;
        return true;
    }

    bool setPointsTotal(double points) {
        if (points < 0.0 || points > pointsTotal) {
            return false;
        }
        this->pointsTotal = points;
        return true;
    }

    void setDate(const Date& date) {
        this->date = date;
    }
};

void printExamResult(const ExamResult& e, ostream& os = cout) {
    os << "Grade: " << e.getGrade() << ", Date: ";
    printDate(e.getDate(), os);
    os << '\n';
}

class ResultsTracker {
private:
    ExamResult* results = nullptr;
    size_t count;
    size_t capacity;

    void resize(size_t newCapacity) {
        ExamResult* resized = new ExamResult[newCapacity];
        for (size_t i = 0; i < count; i++) {
            resized[i] = results[i];
        }

        delete[] results;
        results = resized;
        capacity = newCapacity;
    }

public:
    ResultsTracker() : ResultsTracker(8) {}

    explicit ResultsTracker(size_t capacity) : capacity(capacity), count(0) {
        results = new ExamResult[capacity];
    }

    ~ResultsTracker() {
        delete[] results;
        results = nullptr;
        count = 0;
        capacity = 0;
    }

    size_t getCount() const {
        return count;
    }

    void addResult(const ExamResult& result) {
        if (count >= capacity) {
            resize(capacity * 2);
        }
        results[count++] = result;
    }

    double getAverageGrade() const {
        if (count == 0) {
            return 0.0;
        }

        double percentageSum = 0.0;
        for (size_t i = 0; i < count; i++) {
            percentageSum += results[i].getGrade();
        }
        return percentageSum / count;
    }

    double getHighestGrade() const {
        double max = 0.0;
        for (size_t i = 0; i < count; i++) {
            if (results[i].getGrade() > max) {
                max = results[i].getGrade();
            }
        }
        return max;
    }

    void printAllResults() const {
        for (size_t i = 0; i < count; i++) {
            printExamResult(results[i]);
        }
    }

};

int main() {
    //...
}
