#include <iostream>
#include <cstring>
#include <fstream>
const int MAX_NAME_LENGTH = 31;
const int BUFF_SIZE = 100;
using namespace std;
void strAppend(char* dest, const char* src) {
	while (*dest) {
		dest++;
	}
	while (*src) {
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}
char* numtochar(int num) {
	char* result = new char[3];
	if (num < 10) {
		result[0] = '0';
		result[1] = '0' + num;
		result[2] = '\0';
	}
	else {
		result[0] = '0' + num / 10;
		result[1] = '0' + num % 10;
		result[2] = '\0';
	}
	return result;
}
class Time
{
private:
	int hour;
	int minute;
	int second;
public:
	int toSeconds() const {
		int totalSeconds = hour * 3600 + minute * 60 + second;
		return totalSeconds;
	}
	void addSeconds(int delta) {
		int totalSeconds = toSeconds() + delta;
		hour = (totalSeconds / 3600) % 24;
		minute = (totalSeconds % 3600) / 60;
		second = totalSeconds % 60;
	}
	bool isBefore(const Time& other) const {
		return toSeconds() < other.toSeconds();
	}
	bool isAfter(const Time& other) const {
		return toSeconds() > other.toSeconds();
	}
	bool setTime(char input[9]) {
		int h = 0, m = 0, s = 0;
		h = (input[0] - '0') * 10 + (input[1] - '0');
		m = (input[3] - '0') * 10 + (input[4] - '0');
		s = (input[6] - '0') * 10 + (input[7] - '0');
		if (h < 0 || h >= 24 || m < 0 || m >= 60 || s < 0 || s >= 60) {
			return false;
		}
		hour = h;
		minute = m;
		second = s;
		return true;
	}
	char* printTime() const {
		char* result = new char[9] {'\0'};
		char* hourStr = numtochar(hour);
		strAppend(result, hourStr);
		delete[] hourStr;
		strAppend(result, ":");
		char* minuteStr = numtochar(minute);
		strAppend(result, minuteStr);
		delete[] minuteStr;
		strAppend(result, ":");
		char* secondStr = numtochar(second);
		strAppend(result, secondStr);
		delete[] secondStr;
		return result;
	}
};
enum class dayofWeek {
	Monday = 1,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Unknown
};
enum class subject {
	OOP,
	DSTR2,
	GEOMETRY,
	DIS2,
	Unknown
};
subject charToSubject(char* input) {
	if (strcmp(input, "OOP") == 0) {
		return subject::OOP;
	}
	else if (strcmp(input, "DSTR2") == 0) {
		return subject::DSTR2;
	}
	else if (strcmp(input, "GEOMETRY") == 0) {
		return subject::GEOMETRY;
	}
	else if (strcmp(input, "DIS2") == 0) {
		return subject::DIS2;
	}
	else {
		return subject::Unknown;
	}
}
char* subjectToString(subject sub) {
	switch (sub)
	{
	case subject::OOP:
		return new char[4] {"OOP"};
	case subject::DSTR2:
		return new char[6] {"DSTR2"};
	case subject::GEOMETRY:
		return new char[9] {"GEOMETRY"};
	case subject::DIS2:
		return new char[5] { "DIS2"};
	default:
		return new char[9] {"Unknown"};
	}
}
dayofWeek intToDayofWeek(int day) {
	switch (day)
	{
	case 1:
		return dayofWeek::Monday;
	case 2:
		return dayofWeek::Tuesday;
	case 3:
		return dayofWeek::Wednesday;
	case 4:
		return dayofWeek::Thursday;
	case 5:
		return dayofWeek::Friday;
	default:
		return dayofWeek::Unknown;
	}
}
char* dayofWeekToString(dayofWeek day) {
	char* result = new char[10] {'\0'};
	switch (day)
	{
	case dayofWeek::Monday:
		return new char[7] { "Monday"};
	case dayofWeek::Tuesday:
		return new char[8] { "Tuesday"};
	case dayofWeek::Wednesday:
		return new char[10] {"Wednesday"};
	case dayofWeek::Thursday:
		return new char[10] { "Thursday"};
	case dayofWeek::Friday:
		return new char[7] {"Friday"};
	default:
		return new char[9] {"Unknown"};
	}
	return result;
}
class Occupation {
private:
	char name[MAX_NAME_LENGTH];
	dayofWeek day = dayofWeek::Unknown;
	subject subject = subject::Unknown;
	Time startTime;
	Time endTime;
public:
	dayofWeek getDay() const { return day; }
	const char* getRoom() const { return name; }

	bool isOverlapping(const Occupation& other) const {
		if (day != other.day) return false;
		if (strcmp(name, other.name) != 0) return false; // различна зала

		return startTime.toSeconds() < other.endTime.toSeconds() &&
			endTime.toSeconds() > other.startTime.toSeconds();
	}
	bool createOccupation(char* input) {
		int index = 0;
		int tempindex = 0;
		char tempDay = '0';
		while (input[index] != '\0' && input[index] != ',') {
			tempDay = input[index];
			index++;
			tempindex++;
		}
		day = intToDayofWeek(int(tempDay) - int('0'));
		tempindex = 0;
		index++;
		while (input[index] != '\0' && input[index] != ',') {
			name[tempindex] = input[index];
			tempindex++;
			index++;
		}
		name[tempindex] = '\0';
		tempindex = 0;
		index++;
		char tempSubject[10]{ '\0' };
		while (input[index] != '\0' && input[index] != ',') {
			tempSubject[tempindex] = input[index];
			index++;
			tempindex++;
		}
		tempSubject[tempindex] = '\0';
		subject = charToSubject(tempSubject);
		tempindex = 0;
		index++;
		char tempStartTime[9]{ '\0' };
		while (input[index] != '\0' && input[index] != ',') {
			tempStartTime[tempindex] = input[index];
			index++;
			tempindex++;
		}
		tempStartTime[tempindex] = '\0';
		if (!startTime.setTime(tempStartTime)) {
			return false;
		}
		tempindex = 0;
		index++;
		char tempEndTime[9]{ '\0' };
		while (input[index] != '\0')
		{
			tempEndTime[tempindex] = input[index];
			index++;
			tempindex++;
		}
		tempEndTime[tempindex] = '\0';
		if (!endTime.setTime(tempEndTime)) {
			return false;
		}
		return true;
	}
	void printOccupation() const {
		std::cout << "Name: " << name << std::endl;
		std::cout << "Day: " << dayofWeekToString(day) << std::endl;
		std::cout << "Subject: " << subjectToString(subject) << std::endl;
		std::cout << "Start Time: " << startTime.printTime() << std::endl;
		std::cout << "End Time: " << endTime.printTime() << std::endl;
	}
};
class Schedule
{
private:
	Occupation* occupations = nullptr;
	int size = 0;

public:
	bool addOccupation(const Occupation& occ)
	{
		for (int i = 0; i < size; i++)
		{
			if (occupations[i].isOverlapping(occ))
				return false;
		}

		Occupation* temp = new Occupation[size + 1];

		for (int i = 0; i < size; i++)
			temp[i] = occupations[i];

		temp[size] = occ;

		delete[] occupations;
		occupations = temp;
		size++;

		return true;
	}

	void printSchedule() const
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << "Occupation " << i + 1 << ":\n";
			occupations[i].printOccupation();
			std::cout << "\n";
		}
	}

	Occupation* filterByDay(dayofWeek d, int& sizeo) const
	{
		int counter = 0;
		for (int i = 0; i < size; i++)
		{
			if (occupations[i].getDay() == d) {
				counter++;
			}
		}
		Occupation* result = new Occupation[counter];
		sizeo = 0;
		for (int i = 0; i < size; i++)
		{
			if (occupations[i].getDay() == d) {
				result[sizeo] = occupations[i];
				sizeo++;
			}
		}
		return result;
	}

	Occupation* filterByRoom(const char* room, int& sizeo) const
	{
		int counter = 0;
		for (int i = 0; i < size; i++)
		{
			if (strcmp(occupations[i].getRoom(), room) == 0) {
				counter++;
			}
		}
		Occupation* result = new Occupation[counter];
		sizeo = 0;
		for (int i = 0; i < size; i++)
		{
			if (strcmp(occupations[i].getRoom(), room) == 0) {
				result[sizeo] = occupations[i];
				sizeo++;
			}
		}
		return result;
	}
};
int main()
{
	std::ifstream inputfile("schedule.txt");
	if (!inputfile.is_open()) {
		std::cout << "Failed to open file." << std::endl;
		return -1;
	}
	Schedule schedule;
	int index = 0;
	while (!inputfile.eof()) {
		char buff[BUFF_SIZE];
		inputfile.getline(buff, BUFF_SIZE);
		Occupation occ;
		occ.createOccupation(buff);
		schedule.addOccupation(occ);
	}
	inputfile.close();
	std::cout << "Schedule:" << std::endl;
	schedule.printSchedule();
	int sizeo = 0;
	Occupation* filteredByDay = schedule.filterByDay(dayofWeek::Monday,sizeo);
	std::cout << "Filtered by Monday:" << std::endl;
	for (int i = 0; i < sizeo; i++) {
		filteredByDay[i].printOccupation();
		std::cout << std::endl;
	}
	delete[] filteredByDay;

	sizeo = 0;
	Occupation* filteredByRoom = schedule.filterByRoom("325", sizeo);
	std::cout << "Filtered by 325:" << std::endl;
	for (int i = 0; i < sizeo; i++) {
		filteredByRoom[i].printOccupation();
		std::cout << std::endl;
	}
	delete[] filteredByRoom;
}