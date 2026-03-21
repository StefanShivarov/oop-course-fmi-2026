
#include <iostream>
#include <print>
#include <format>
#include <cstring>
#pragma warning(disable : 4996)

using std::cin;
using std::cout;
using std::println;

enum class Subject {
	OOP, GEOMETRY, DSTR2, DIS2, ENGLISH
};

const char* toString(const Subject& s) {
	switch (s) {
	case Subject::OOP: return "OOP";
	case Subject::GEOMETRY: return "GEOMETRY";
	case Subject::DSTR2: return "DSTR2";
	case Subject::DIS2: return "DIS2";
	case Subject::ENGLISH: return "ENGLISH";
	default:
		return "other";
	}
}

class Date {
	int day = 1;
	int month = 1;
	int year = 2000;
	bool isYearLeap(int year) const {
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			return true;

		return false;
	}

	int daysInMonth(int m, int y) const {
		if (m == 2) {
			if (isYearLeap(y)) {
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
	Date(int day=1, int month=1, int year=2000) {
		if (isValidDate(day, month, year)) {
			this->day = day;
			this->month = month;
			this->year = year;
		}
	}

	void printDate() const {
		println("Date: {}.{}.{}", day, month, year);
	}
};

class Exam {
	Subject subject;
	double grade = 0.00;
	Date date;
public:
	Exam() : subject(Subject::OOP), grade(2.0), date() {}
	Exam(double grade, const Date& date, const Subject& subject) : date(date), subject(subject) {
		setGrade(grade);
	}

	double getGrade() const {
		return grade;
	}

	const Date& getDate() const {
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
	}
};

class StudentResults {
	Exam* exams = nullptr;
	int count = 0;

public:

	StudentResults(int count = 0) : count(count) {
		if (count > 0)
			exams = new Exam[count];
	}

	~StudentResults() {
		delete[] exams;
	}

	void setExam(int index, const Exam& exam) {
		if (index >= 0 && index < count) {
			exams[index] = exam;
		}
	}

	void printAll() const {
		for (int i = 0; i < count; i++) {
			cout << "Exam " << i + 1 << ':' << std::endl;
			exams[i].printExamInfo();
			cout << std::endl;
		}
	}

	double getBestGrade() const {
		if (count == 0) return 0;

		double best = exams[0].getGrade();

		for (int i = 1; i < count; i++) {
			if (exams[i].getGrade() > best) {
				best = exams[i].getGrade();
			}
		}

		return best;
	}

	double getAverageGrade() const {
		if (count == 0) return 0;

		double sum = 0;

		for (int i = 0; i < count; i++) {
			sum += exams[i].getGrade();
		}

		return sum / count;
	}

	void addExam(const Exam& newExam) {

		Exam* newArr = new Exam[count + 1];

		for (int i = 0; i < count; i++) {
			newArr[i] = exams[i];
		}

		newArr[count] = newExam;

		delete[] exams;

		exams = newArr;
		count++;
	}
};


int main()
{
	Date d1(10, 3, 2025);
	Date d2(15, 3, 2025);
	Date d3(20, 3, 2025);

	Exam e1(5.50, d1, Subject::OOP);
	Exam e2(4.25, d2, Subject::GEOMETRY);

	StudentResults results(2);

	results.setExam(0, e1);
	results.setExam(1, e2);

	println("\n--- All Exams ---");
	results.printAll();

	println("\nBest grade: {}", results.getBestGrade());
	println("Average grade: {}", results.getAverageGrade());

	Exam e3(6.00, d3, Subject::ENGLISH);

	results.addExam(e3);

	println("\n--- After Adding Exam ---");
	results.printAll();
}


