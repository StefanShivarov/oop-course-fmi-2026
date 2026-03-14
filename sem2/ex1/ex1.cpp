#include <iostream>
#include <fstream>
#include <format>
#include <print>

using std::cin;
using std::cout;

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

int readTimesFromFile(Time* times) {
	std::ifstream file("times.txt");

	if (!file.is_open()) {
		cout << "Error opening file!";
		return -1;
	}

	int h, m, s;
	char deliminator;

	int count = 0;

	while (file >> h >> deliminator >> m >> deliminator >> s) {
		times[count].setTime(h, m, s);
		count++;
	}

	file.close();

	return count;
}

void sortTimes(Time* times, int size) {
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (times[j].isAfter(times[j + 1])) {
				std::swap(times[j], times[j + 1]);
			}
		}
	}
}

void saveTimes(Time* times, int size) {
	std::ofstream file("times.txt");

	if (!file.is_open()) {
		cout << "Error!";
		return;
	}

	for (int i = 0; i < size; i++)
	{
		file << std::format("{:02}:{:02}:{:02}", times[i].getHour(), times[i].getMinutes(), times[i].getSeconds()) << '\n';
	}

	file.close();
}

int main()
{
	Time times[100];

	int count = readTimesFromFile(times);

	sortTimes(times, count);
	saveTimes(times, count);
}
