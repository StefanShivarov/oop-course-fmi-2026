#include <iostream>
#include <print>
#include "Time.h"

#pragma warning(disable:4996)

namespace Constants {
	constexpr int MaxSubjectNameLength = 31;
	constexpr int MaxRoomNameLength = 15;
	constexpr int MaxScheduleClassesCount = 64;
	constexpr char FileName[13] = "schedule.txt";
	constexpr int ValidTimestampLength = 8;
}

enum class DayOfWeek {
	Monday = 1,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
};

class Class {
private:
	char room[Constants::MaxRoomNameLength + 1];
	char subject[Constants::MaxSubjectNameLength + 1];
	DayOfWeek dayOfWeek;
	Time startTime;
	Time endTime;

public:
	void setRoom(const char* room) {
		if (strlen(room) > Constants::MaxRoomNameLength) return;
		std::strcpy(this->room, room);
	}

	const char* getRoom() const {
		return room;
	}

	void setSubject(const char* subject) {
		if (strlen(subject) > Constants::MaxSubjectNameLength) return;
		std::strcpy(this->subject, subject);
	}

	const char* getSubject() const {
		return subject;
	}

	void setDayOfWeek(DayOfWeek dayOfWeek) {
		this->dayOfWeek = dayOfWeek;
	}

	void setDayOfWeek(int dayOfWeek) {
		if (dayOfWeek < 1 || dayOfWeek > 7) return;

		switch (dayOfWeek) {
		case 1: this->dayOfWeek = DayOfWeek::Monday; break;
		case 2: this->dayOfWeek = DayOfWeek::Tuesday; break;
		case 3: this->dayOfWeek = DayOfWeek::Wednesday; break;
		case 4: this->dayOfWeek = DayOfWeek::Thursday; break;
		case 5: this->dayOfWeek = DayOfWeek::Friday; break;
		case 6: this->dayOfWeek = DayOfWeek::Saturday; break;
		case 7: this->dayOfWeek = DayOfWeek::Sunday; break;
		}
	}

	DayOfWeek getDayOfWeek() const {
		return dayOfWeek;
	}

	int getDayOfWeekAsInt() const {
		switch (dayOfWeek) {
		case DayOfWeek::Monday: return 1;
		case DayOfWeek::Tuesday: return 2;
		case DayOfWeek::Wednesday: return 3;
		case DayOfWeek::Thursday: return 4;
		case DayOfWeek::Friday: return 5;
		case DayOfWeek::Saturday: return 6;
		case DayOfWeek::Sunday: return 7;
		}
	}

	void setTimes(const Time& startTime, const Time& endTime) {
		if (!startTime.isBefore(endTime)) return;

		this->startTime = startTime;
		this->endTime = endTime;
	}

	Time getStartTime() const {
		return startTime;
	}

	Time getEndTime() const {
		return endTime;
	}

	void setAll(const char* room, const char* subject, DayOfWeek dayOfWeek, const Time& startTime, const Time& endTime) {
		setRoom(room);
		setSubject(subject);
		setDayOfWeek(dayOfWeek);
		setTimes(startTime, endTime);
	}

	void print(std::ostream& os = std::cout) const {
		std::print(os, "{},", getDayOfWeekAsInt());
		std::print(os, "{},", room);
		std::print(os, "{},", subject);
		startTime.writeToStream(os);
		std::print(os, ",");
		endTime.writeToStream(os);
	}
};

class Schedule {
private:
	Class classes[Constants::MaxScheduleClassesCount];
	int classCount = 0;

	bool checkIfClassOverlaps(const Class& newClass) const {
		for (int i = 0; i < classCount; i++) {
			const Class& existingClass = classes[i];
			if (existingClass.getDayOfWeek() != newClass.getDayOfWeek()) continue;
			if (strcmp(existingClass.getRoom(), newClass.getRoom())) continue;

			if (existingClass.getStartTime().isBefore(newClass.getEndTime()) &&
				existingClass.getEndTime().isAfter(newClass.getStartTime())) {
				return true;
			}
		}

		return false;
	}

public:
	int getClassCount() const {
		return classCount;
	}

	bool addClass(Class& newClass) {
		if (checkIfClassOverlaps(newClass)) return false;

		classes[classCount] = newClass;
		classCount++;
	}

	void printSchedule(std::ostream& os = std::cout) const {
		for (int i = 0; i < classCount; i++) {
			classes[i].print(os);
			std::println(os);
		}
	}

	void printScheduleForDayOfWeek(DayOfWeek day, std::ostream& os = std::cout) const {
		for (int i = 0; i < classCount; i++) {
			if (classes[i].getDayOfWeek() == day) {
				classes[i].print(os);
				std::println(os);
			}
		}
	}

	void printScheduleForDayOfWeek(int day, std::ostream& os = std::cout) const {
		for (int i = 0; i < classCount; i++) {
			if (classes[i].getDayOfWeekAsInt() == day) {
				classes[i].print(os);
				std::println(os);
			}
		}
	}

	void printScheduleForRoom(const char* room, std::ostream& os = std::cout) const {
		for (int i = 0; i < classCount; i++) {
			if (strcmp(classes[i].getRoom(), room) == 0) {
				classes[i].print(os);
				std::println(os);
			}
		}
	}

	void saveToFile(const char* fileName = Constants::FileName) const {
		std::ofstream file(fileName);

		if (!file.is_open()) {
			std::println("Failed to open file for writing.");
			return;
		}

		printSchedule(file);
	}
};

int main() {
	Schedule schedule;
	Class c1;
	c1.setAll("101", "Mathematics", DayOfWeek::Monday, Time{ 9, 0, 0 }, Time{ 10, 30, 0 });
	schedule.addClass(c1);

	Class c2;
	c2.setAll("101", "Physics", DayOfWeek::Tuesday, Time{ 10, 0, 0 }, Time{ 11, 30, 0 });
	schedule.addClass(c2);

	Class c3;
	c3.setAll("101", "Chemistry", DayOfWeek::Monday, Time{ 10, 0, 0 }, Time{ 11, 0, 0 });
	schedule.addClass(c3);

	Class c4;
	c4.setAll("102", "Biology", DayOfWeek::Monday, Time{ 9, 30, 0 }, Time{ 10, 30, 0 });
	schedule.addClass(c4);

	std::println("Schedule:");
	schedule.printSchedule();

	std::println("Monday schedule:");
	schedule.printScheduleForDayOfWeek(DayOfWeek::Monday);

	std::println("Room 101 schedule:");
	schedule.printScheduleForRoom("101");

	schedule.saveToFile();
}