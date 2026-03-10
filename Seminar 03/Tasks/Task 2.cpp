#include <iostream>

const int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date {
private:
	int day;
	int month;
	int year;


	bool isLeapYear(int y) const {
		return (y % 4 == 0) && (y % 400 == 0 || y % 100 != 0);
	}

	int getDaysInMonth(int m, int y) const {
		if (m < 1 || m >12)
		{
			return 0;
		}
		if (m == 2)
		{
			if (isLeapYear(y))
			{
				return 29;
			}
			return 28;
		}
		return daysInMonth[m - 1];
	}

	bool isValidCombination(int d, int m, int y) const {
		if (y < 2025)
		{
			return false;
		}
		if (m < 1 || m > 12)
		{
			return false;
		}
		int daysInMonth = getDaysInMonth(m, y);
		if (d < 1 || d > daysInMonth)
		{
			return false;
		}
		return true;
	}

public:
	Date() {
		day = 1;
		month = 10;
		year = 2025;
	}
	Date(int d, int m, int y) {
		if (!isValidCombination(d, m, y))
		{

			day = 0;
			month = 0;
			year = 0;
		}
		else
		{
			day = d;
			month = m;
			year = y;
		}
	}
	bool isDateValid()const {
		if (isValidCombination(day, month, year))
		{
			return true;
		}
		return false;
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
	void setDate(Date date) {
		if (date.isDateValid())
		{
			day = date.getDay();
			month = date.getMonth();
			year = date.getYear();
		}
		else
		{
			day = 0;
			month = 0;
			year = 0;
		}
	}
};

class Test {
private:
	Date date;
	double grade;
public:
	Test() {
		date;
		grade = 2.0;
	}
	Test(Date date, double grade) {
		this->date = date;
		if (grade >= 2.0 && grade <= 6.0)
		{
			this->grade = grade;
		}
		else
		{
			this->grade = 2.0;
		}
	}
	const Date& getDate() const {
		return date;
	}
	double getGrade() const {
		return grade;
	}
	void setGrade(double grade) {
		if (grade >= 2.0 && grade <= 6.0)
		{
			this->grade = grade;
		}
		else
		{
			this->grade = 2.0;
		}
	}
	void setDate(Date date) {
		/*if (date.isDateValid())
		{
			this->date = date;
		}
		else
		{
			this->date = { 0, 0, 0 };
		}*/
		this->date.setDate(date);
	}
};

class Result {
private:
	Test* result = nullptr;
	int count;
public:
	Result() : count(0) {

	}
	Result(int count) : count(count) {
		result = new Test[count];
	}
	~Result() {
		delete[] result;
		result = nullptr;

	}
	const Test& getResultInPosition(int index) const {
		return result[index];
	}
	void printAllResults() const {
		if (count == 0)
		{
			return;
		}
		for (int i = 0; i < count; i++)
		{
			std::cout << result[i].getGrade() << " on " << result[i].getDate().getDay() << "." << result[i].getDate().getMonth() << "." << result[i].getDate().getYear() << std::endl;
		}
	}

	double getBestResult() const {
		double highestGrade = 0.0;
		if (count == 0)
		{
			return 0;
		}
		for (int i = 0; i < count; i++)
		{
			if (result[i].getGrade() > highestGrade) {
				highestGrade = result[i].getGrade();
			}
		}
		return highestGrade;
	}

	double getAverageResult() const {
		double sum = 0;
		if (count == 0)
		{
			return 0;
		}
		for (int i = 0; i < count; i++)
		{
			sum += result[i].getGrade();
		}
		return sum / count;
	}

	void addTest(const Test& newTest) {
		int newSize = count + 1;
		Test* newResult = new Test[newSize];
		for (int i = 0; i < count; i++)
		{
			newResult[i] = result[i];
		}
		newResult[newSize - 1] = newTest;
		delete[] result;
		result = newResult;
		count = newSize;
	}

	void setGradeAtIndex(int index, double grade) {
		if (index >= 0 && index < count) {
			if (grade >= 2.0 && grade <= 6.0)
			{
				result[index].setGrade(grade);
			}
			else
			{
				result[index].setGrade(2.0);
			}
		}
	}
};

int main()
{
	Result grades(0);

	Date d1(15, 10, 2025);
	Date d2(3, 11, 2025);

	Test t1(d1, 5.70);
	Test t2(d2, 4.50);

	grades.addTest(t1);
	grades.addTest(t2);
	std::cout << "Average: " << grades.getAverageResult() << std::endl;
	std::cout << "Best: " << grades.getBestResult() << std::endl;
	grades.printAllResults();
}
