#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::ostream;

class Date{
    private:
        int day = 24;
        int month = 2;
        int year = 1999;
        int DAYS_IN_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
        bool isLeapYear(int year) const {
            return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
        }

        int getMaxDaysForMonth(int month, int year) const {
            if (month < 1 || month > 12) {
                return 0;
            }
            if (month == 2 && isLeapYear(year)) {
                return 29;
            }
            return DAYS_IN_MONTH[month - 1];
        }

        bool isValidDate(int day, int month, int year) const {
            if (year < 1) {
                return false;
            }
            if (month < 1 || month > 12) {
                return false;
            }
            if (day < 1 || day > getMaxDaysForMonth(month, year)) {
                return false;
            }
            return true;
        }
    public:
        Date() = default;
        Date(int day, int month, int year) {
            if (isValidDate(day, month, year)) {
                this->day = day;
                this->month = month;
                this->year = year;
            }
        }

        int getDay() const {
            return day;
        }
        int getMonth() const {
            return month;
        }
        int getYear() const {
            return year;
        }

        void setDay(const int day) {
            if (isValidDate(day, month, year)) {
                this->day = day;
            }
        }

        void setMonth(const int month) {
            if (isValidDate(day, month, year)) {
                this->month = month;
            }
        }

        void setYear(const int year) {
            if (isValidDate(day, month, year)) {
                this->year = year;
            }
        }

        void printDate(ostream& os = cout) const {
            if (day < 10) {
                os << '0';
            }
            os << day << '/';

            if (month < 10) {
                os << '0';
            }
            os << month << '/';

            os << year;
        }
};


class ExamGrade {
    private:
        double grade = 2.0;
        Date date;
    public:
        ExamGrade() = default;
        ExamGrade(double grade, const Date& date) : date(date) {
            setGrade(grade);
        }

        double getGrade() const {
            return grade;
        }
        const Date& getDate() const {
            return date;
        }

        void setGrade(double grade) {
            if (grade >= 2.00 && grade <= 6.00) {
                this->grade = grade;
            }
        }
        
        void printResults(ostream& os = cout) const {
            os << "Grade: " << grade << endl;
            date.printDate(os);
        }
};

class Results {
    private:
        ExamGrade* results = nullptr;
        size_t count = 0;
        size_t capacity = 0;

        void resize(size_t newCap) {
            ExamGrade* resized = new ExamGrade[newCap];
            for (size_t i = 0; i < count; i++) {
                resized[i] = results[i];
            }

            delete[] results;
            results = resized;
            capacity = newCap;
        }
    public:
        Results() : Results(10) {}
        explicit Results(size_t capacity) : count(0), capacity(capacity) {
            results = new ExamGrade[capacity];
        }
        ~Results() {
            delete[] results;
            results = nullptr;
            count = 0;
            capacity = 0;
        }

        size_t getCount() const {
            return count;
        }

        void addResult(const ExamGrade& result) {
            if (count >= capacity) {
                resize(capacity + 10);
            }
            results[count++] = result;
        }

        double getAverageGrade() const {
            if (count == 0) {
                return 0;
            }
            double sum = 0;
            for (size_t i = 0; i < count; i++) {
                sum += results[i].getGrade();
            }
            return sum / count;
        }

        double getHighestGrade() const {
            if (count == 0) {
                return 0;
            }
            if (count == 1) {
                return results[0].getGrade();
            }
            double highestGrade = 0;
            for (size_t i = 0; i < count; i++) {
                if (results[i].getGrade() > highestGrade) {
                    highestGrade = results[i].getGrade();
                }
            }
            return highestGrade;
        }

        void printResults() const {
            for (size_t i = 0; i < count; i++) {
                results[i].printResults();
            }
        }
};

int main() {
    Date date1(5, 9, 2026);
    Date date2(29, 2, 2024);

    date1.printDate(); 
    cout << endl;
    date2.printDate(); 
    cout << endl << endl;

    ExamGrade grade1(5.5, date1);
    ExamGrade grade2(6.0, date2);

    grade1.printResults(); 
    cout << endl;
    grade2.printResults(); 
    cout << endl;

    Results results;
    results.addResult(grade1);
    results.addResult(grade2);

    cout << "\nCount: " << results.getCount() << endl;
    cout << "Avg: " << results.getAverageGrade() << endl;
    cout << "Max: " << results.getHighestGrade() << endl;

    return 0;
}