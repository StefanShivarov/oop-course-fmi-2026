#include <iostream>
#include <fstream>
const int BUFF_SIZE = 100;
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
	bool isBefore(const Time& other) const{
		return toSeconds() < other.toSeconds();
	}
	bool isAfter(const Time& other) const{
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
void swap(Time& a, Time& b) {
	Time temp = a;
	a = b;
	b = temp;
}
void bubbleSort(Time arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j].isAfter(arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}
int main()
{
	std::ifstream inputfile("time.txt");
	if (!inputfile.is_open()) {
		std::cout << "Failed to open file." << std::endl;
		return -1;
	}
	int numberOfLines = 0;
	while (!inputfile.eof()) {
		numberOfLines++;
		char buff[BUFF_SIZE];
		inputfile.getline(buff, BUFF_SIZE);
	}
	inputfile.seekg(0, std::ios::beg);
	Time* times = new Time[numberOfLines];
	int index = 0;
	while (!inputfile.eof()) {
		char buff[BUFF_SIZE];
		inputfile.getline(buff, BUFF_SIZE);
		times[index].setTime(buff);
		index++;
	}
	inputfile.close();

	bubbleSort(times, numberOfLines);

	std::ofstream outputFile("sorted_time.txt");
	if (!outputFile.is_open()) {
		std::cout << "Failed to open file." << std::endl;
		return -1;
	}

	for (int i = 0; i < numberOfLines; i++) {
		char* timeStr = times[i].printTime();
		std::cout << timeStr << std::endl;
		outputFile << timeStr << std::endl;
		delete[] timeStr;
	}
	outputFile.close();
}