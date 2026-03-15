#include <iostream>
#include <print>

// Date class from the repo
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
    Date(int y, int m, int d) {
		this->setAll(y, m, d);
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
        std::print("{}/{}/{}", year, month, day);
	}
};

class Exam {
private:
	double grade;
    Date date;

public:
	Exam(double grade, Date date) {
        setGrade(grade);
        setDate(date);
	}

	Exam(double grade, int year, int month, int day) {
        setGrade(grade);
        setDate(year, month, day);
    }

    bool setGrade(double grade) {
        if (grade < 2.0 || grade > 6.0) {
            return false;
		}

        this->grade = grade;
		return true;
	}

    bool setDate(Date d) {
        date = d;
        return true;
    }

    bool setDate(int year, int month, int day) {
        return date.setAll(year, month, day);
    }

    double getGrade() const {
        return grade;
    }

    Date getDate() const {
        return date;
	}

    void print() const {
        std::print("Grade: {:.2f}, Date: ", grade);
		date.print();
	}
};

class Exams {
private:
	int count = 0;
	int capacity = 4;
    double bestGrade = 0;
    double averageGrade = 0;
	Exam** exams = nullptr;

    void resize() {
        capacity *= 2;
        Exam** newExams = new Exam*[capacity];

        for (int i = 0; i < count; i++) {
            newExams[i] = exams[i];
        }

        for (int i = count; i < capacity; i++) {
            newExams[i] = nullptr;
        }

        delete[] exams;
        exams = newExams;
	}

	void updateStats(Exam* exam) { // for constant time complexity
        if (exam->getGrade() > bestGrade) {
            bestGrade = exam->getGrade();
        }

		averageGrade = (averageGrade * count + exam->getGrade()) / (count + 1);
	}

public:
    Exams() {
		exams = new Exam* [capacity];
    }

    Exams(int capacity) {
        if (capacity < 0) {
            capacity = 0;
        }

		this->capacity = capacity;

		exams = new Exam* [capacity];

        for (int i = 0; i < capacity; i++) {
            addExam();
		}
    }

    int getCount() const {
        return count;
	}

    int getCapacity() const {
        return capacity;
    }

    bool addExam(Exam* exam) {
        if (exam == nullptr) {
            return false;
        }

        if (count >= capacity) {
            resize();
        }

		updateStats(exam);

        exams[count++] = exam;
        return true;
	}

    bool addExam(std::istream& is = std::cin) {
        double grade;
		int year, month, day;

        is >> grade;

        is >> year >> month >> day;

        Date date (year, month, day);
        Exam* exam = new Exam(grade, date);
		return addExam(exam);
    }

    double getBestGrade() const {
        return bestGrade;
	}

    double getAverageGrade() const {
        return averageGrade;
    }

    void print() const {
        std::println("Grades overview:");
		std::println("Count: {}", count);
		std::println("Best grade: {:.2f}, Average grade: {:.2f}", bestGrade, averageGrade);
        for (int i = 0; i < count; i++) {
            exams[i]->print();
			std::println();
        }
	}

    ~Exams() {
        for (int i = 0; i < count; i++) {
            delete exams[i];
        }

        delete[] exams;
    }
};

int main()
{
	Exams exams(2);

	Date date(2024, 6, 15);
	Exam* exam1 = new Exam (5.5, date);
    Exam* exam2 = new Exam(4.5, date);
    Exam* exam3 = new Exam(2.5, date);

    exams.addExam();
    exams.addExam(exam1);
    exams.addExam(exam2);
    exams.addExam(exam3);

	exams.print();
}