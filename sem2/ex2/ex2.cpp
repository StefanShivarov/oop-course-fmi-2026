#include <iostream>
#include <fstream>
#include <cstring>
#include <format>
#include <print>

using std::cin;
using std::cout;

enum class Day {
	MONDAY = 1, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY
};

enum class Subject {
	OOP, DSTR2, GEOMETRY, DIS2
};

class Time {
private:
	int hour;
	int minutes;
	int seconds;

public:
	int getHour() const {
		return hour;
	}

	int getMinutes() const {
		return minutes;
	}

	int getSeconds() const {
		return seconds;
	}

	void setTime(int h, int m, int s) {
		if (h >= 0 && h <= 23
			&& m >= 0 && m <= 59
			&& s >= 0 && s <= 59) {

			hour = h;
			minutes = m;
			seconds = s;
		}
	}

	int toSeconds() const {
		return seconds + minutes * 60 + hour * 3600;
	}

	bool isBefore(const Time& other) const {

		return (other.toSeconds() > toSeconds());
	}

	bool isAfter(const Time& other) const {

		return (other.toSeconds() < toSeconds());
	}

	void addSeconds(int delta) {
		int totalSeconds = toSeconds() + delta;
		hour = (totalSeconds / 3600) % 24;
		minutes = (totalSeconds % 3600) / 60;
		seconds = (totalSeconds % 3600) % 60;
	}
};

class Lesson {
private:
	char room[31];
	Day day;
	Subject subject;
	Time start;
	Time end;

public:
	const char* getRoom() const {
		return room;
	}

	Day getDay() const {
		return day;
	}

	Subject getSubject() const {
		return subject;
	}

	Time getStartTime() const {
		return start;
	}

	Time getEndTime() const {
		return end;
	}


	void setLesson(const char* r, Day d, Subject sub, Time s, Time e) {
		if (!r) return;

		strcpy_s(room, r);

		day = d;
		subject = sub;

		start = s;
		end = e;
	}

	bool isOverlappintWith(const Time& startOther, const Time& endOther) {
		return start.isBefore(endOther) && startOther.isBefore(end);
	}

};

const char* subjectToStr(Subject sub) {
	switch (sub) {
	case Subject::OOP: return "OOP";
	case Subject::DSTR2: return "DSTR2";
	case Subject::GEOMETRY: return "GEOMETRY";
	case Subject::DIS2: return "DIS2";
	}

	return "unknown";
}

Subject parseSubject(std::ifstream& file) {
	char text[10];
	if (file.getline(text, 10, ',')) {
		if (strcmp(text, "OOP") == 0) {
			return Subject::OOP;
		}
		else if (strcmp(text, "DSTR2") == 0) {
			return Subject::DSTR2;
		}
		else if (strcmp(text, "GEOMETRY") == 0) {
			return Subject::GEOMETRY;
		}
		else if (strcmp(text, "DIS2") == 0) {
			return Subject::DIS2;
		}
	}
}

class Schedule {
private:
	Lesson lesson[100];
	int count = 0;

public:
	int getCountOfLessons() const {
		return count;
	}

	bool addLesson(const char* newRoom, Day newDay, Subject newSubject, const Time& newStart, const Time& newEnd) {
		for (int i = 0; i < count; i++)
		{
			if ((lesson[i].getDay() == newDay)
				&& strcmp(lesson[i].getRoom(), newRoom) == 0
				&& lesson[i].isOverlappintWith(newStart, newEnd)) {

				return false;
			}
		}

		lesson[count].setLesson(newRoom, newDay, newSubject, newStart, newEnd);
		count++;

		return true;
	}

	void filterByDay(Day day) {
		std::ofstream file("filtered_schedule.txt");
		if (!file.is_open()) {
			cout << "error";
			return;
		}

		for (int i = 0; i < count; i++)
		{
			Lesson l = lesson[i];

			if (lesson[i].getDay() == day) {
				file << (int)l.getDay() << ",";
				file << l.getRoom() << ",";
				file << subjectToStr(l.getSubject()) << ",";

				file << l.getStartTime().getHour() << ":"
					<< l.getStartTime().getMinutes() << ":"
					<< l.getStartTime().getSeconds() << ",";

				file << l.getEndTime().getHour() << ":"
					<< l.getEndTime().getMinutes() << ":"
					<< l.getEndTime().getSeconds() << "\n";
			}
		}
		file.close();
	}
};

Time readTime(std::ifstream& file) {
	Time t{};
	int h, m, s;
	char colon;

	if (file >> h >> colon >> m >> colon >> s) {
		t.setTime(h, m, s);
	}

	return t;
}


void readFile(Schedule& mySchedule) {
	std::ifstream file("schedule.txt");

	if (!file.is_open()) {
		cout << "Error opening file";
		return;
	}

	int d;
	char room[31];

	while (file >> d) {

		file.ignore();
		file.getline(room, 31, ',');

		Subject sub = parseSubject(file);

		Time start = readTime(file);

		file.ignore();

		Time end = readTime(file);

		mySchedule.addLesson(room, (Day)d, sub, start, end);
	}

	file.close();
}

int main()
{
	Schedule mySchedule;
	readFile(mySchedule);

	mySchedule.filterByDay(Day::MONDAY);

}