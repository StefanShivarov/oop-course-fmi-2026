#include <iostream>
using namespace std;

class Date {
    int day;
    int month;
    int year;
public:
    Date() : day(0), month(0), year(0) {}
    Date(const int day, const int month, const int year) : day(day), month(month), year(year) {}
    void print() const {
        println("{:02} {:02} {:04}", day, month, year);
    }
};
void resize(double*& grades, Date*& dates, size_t& size) {
    double* newGrades = new double[size + 1];
    Date* newDates = new Date[size + 1];
    for (size_t i = 0; i < size; i++) {
        newGrades[i] = grades[i];
        newDates[i] = dates[i];
    }
    delete[] grades;
    delete[] dates;
    grades = newGrades;
    dates = newDates;
    size++;
}
class Exams {
    double* grades;
    Date* dates;
    size_t size;
    int addedResults = 0;
public:
    Exams(const size_t size) : size(size) {
        grades = new double[size];
        dates = new Date[size];
    }
    ~Exams() {
        delete[] grades;
        delete[] dates;
    }
    void printAllExams() const {
        for (size_t i = 0; i < addedResults; i++) {
            std::print("Exam on: ");
            dates[i].print();
            std::println("Grade: {}", grades[i]);
        }
    }
    double bestResult() const {
        double result = grades[0];
        for (size_t i = 1; i < size; i++) {
            if (grades[i] > result) {
                result = grades[i];
            }
        }
        return result;
    }
    double averageResult() const {
        double result = grades[0];
        for (size_t i = 1; i < size; i++) {
            result += grades[i];
        }
        return result / size;
    }
    void addResult(const double grade, const Date& date) {
        if (addedResults >= size) {
            resize(grades, dates, size);
            println("Resized");
        }
        grades[addedResults] = grade;
        dates[addedResults] = date;
        addedResults++;
    }
};
int main() {
    Exams exams(2);
    Date date1 = Date(1, 1, 2020);
    Date date2 = Date(2, 1, 2020);
    Date date3 = Date(3, 1, 2020);
    exams.addResult(3, date1);
    exams.printAllExams();
    println();
    exams.addResult(4, date2);
    exams.printAllExams();
    println();
    exams.addResult(5, date3);
    exams.printAllExams();
    println();
    println("Average result: {:.2f}", exams.averageResult());
    println("Best result: {:.2f}", exams.bestResult());
}