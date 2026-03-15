#include <iostream>
#include <print>
#include <format>
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
class Test {
private:
	Subject name;
	double grade;
	Date date;
public:
	Test() {
		grade = 0;
	}
	void setGrade(double newGrade) {
		if (newGrade >= 2.0 && newGrade <= 6.0) {
			grade = newGrade;
		}
		else {
			grade = 2.0;
		}
	}
	Test(const Subject& name, double grade, Date date) {
		this->name = name;
		setGrade(grade);
		this->date = date;
	}
	double getGrade() const {
		return grade;
	}

	Date getDate() const {
		return date;
	}

	Subject getName() const {
		return name;
	}

	void setDate(const Date& newDate) {
		this->date = newDate;
	}

	void setName(Subject newSub) {
		name = newSub;
	}
	void printInfo() {
		date.printDate();
		println("Subject: {}\nGrade: {:.2f}", toString(name), grade);
		println(" ");
	}
	~Test() {
	}
};
class Kontrols {
private:
	Test* tests = nullptr;
	int lenght = 0;
public:
	Kontrols() {
		tests = new Test[1];
		lenght = 0;
	}
	void print() {
		for (int i = 0; i < lenght; i++) {
			tests[i].printInfo();
		}
	}
	void addTest(const Test& newTest) {
		if (lenght == 0) {
			tests[0] = newTest;
			lenght++;
		}
		else {

			Test* temp = new Test[lenght+1];
			for (int i = 0; i < lenght; i++) {
				temp[i] = tests[i];
			}
			temp[lenght] = newTest;
			lenght++;
			delete[] tests;
			tests = temp;
		}
	}
	double getBestResult() const {
		double best = tests[0].getGrade();
		for (int i = 1; i < lenght; i++)
		{
			if (best < tests[i].getGrade()) {
				best = tests[i].getGrade();
			}
		}

		return best;
	}

	double getAvgResult() const {
		double sum = 0;
		for (int i = 0; i < lenght; i++)
		{
			sum += tests[i].getGrade();
		}

		return sum / lenght;
	}
	~Kontrols() {
		delete[] tests;
		lenght = 0;
		tests = nullptr;
	}
};
int main()
{
	Kontrols myKontrols;

	Date d1(18, 04, 2026);
	Test test1(Subject::OOP,6.00, d1);

	Date d2(25, 04, 2026);
	Test test2(Subject::GEOMETRY, 5.90, d2);

	Date d3(17, 05, 2026);
	Test test3(Subject::DIS2, 4.2, d3);

	Date d4(30, 05, 2026);
	Test test4(Subject::DSTR2,5.95, d4);


	myKontrols.addTest(test1);
	myKontrols.addTest(test2);
	myKontrols.addTest(test3);
	myKontrols.addTest(test4);

	println("The average result is {:.2f}", myKontrols.getAvgResult());

	println("The best result is {:.2f}", myKontrols.getBestResult());

	std::cout << '\n';

	println("--- My Exams Information ---");
	std::cout << '\n';
	myKontrols.print();
}