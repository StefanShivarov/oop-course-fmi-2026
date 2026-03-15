#include <iostream>
using namespace std;
const int MAX_MESSAGE = 100;
enum LogType
{
	Info,
	Warn,
	Error,
	Debug,
	Unknown
};
LogType CharToLogType(char c)
{
	switch (c)
	{
	case 'I': return Info;
	case 'W': return Warn;
	case 'E': return Error;
	case 'D': return Debug;
	default:  return Unknown;
	}
}
const char* LogTypeToString(LogType t)
{
	switch (t)
	{
	case Info:  return "I";
	case Warn:  return "W";
	case Error: return "E";
	case Debug: return "D";
	default:    return "?";
	}
}
struct Log
{
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
	int totalseconds = 0;
	LogType type = Unknown;
	char message[MAX_MESSAGE];

	void print() const {
		std::cout << (hours < 10 ? "0" : "") << hours << ":"
			<< (minutes < 10 ? "0" : "") << minutes << ":"
			<< (seconds < 10 ? "0" : "") << seconds << " "
			<< LogTypeToString(type) << " "
			<< message << "\n";
	}

	void calculate() {
		totalseconds = hours * 3600 + minutes * 60 + seconds;
	}
};
void Sort(Log* logs, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (logs[j].totalseconds > logs[j + 1].totalseconds) {
				Log temp = logs[j + 1];
				logs[j + 1] = logs[j];
				logs[j] = temp;
			}
		}
	}
}
void Statistic(Log* logs, int size) {
	int count[4] = { 0 };

	for (int i = 0; i < size; i++) {
		if (logs[i].type != Unknown)
			count[logs[i].type]++;
	}

	std::cout << "Statistics:\n";
	std::cout << "Info: " << count[Info] << "\n";
	std::cout << "Warn: " << count[Warn] << "\n";
	std::cout << "Error: " << count[Error] << "\n";
	std::cout << "Debug: " << count[Debug] << "\n";
}
void EarliestandLatest(Log* logs, int size) {
	Log* logsCopy = new Log[size];
	for (int i = 0; i < size; i++) {
		logsCopy[i] = logs[i];
	}

	Sort(logsCopy, size);

	std::cout << "Earliest log:\n";
	logsCopy[0].print();

	std::cout << "Latest log:\n";
	logsCopy[size - 1].print();

	delete[] logsCopy;
}
void FilterByTime(Log* logs, int size, int t1, int t2) {
	std::cout << "Logs between " << (t1 / 3600) << ":" << ((t1 % 3600) / 60) << ":" << (t1 % 60)
		<< " and " << (t2 / 3600) << ":" << ((t2 % 3600) / 60) << ":" << (t2 % 60) << ":\n";
	for (int i = 0; i < size; i++) {
		if (logs[i].totalseconds >= t1 && logs[i].totalseconds <= t2) {
			logs[i].print();
		}
	}
}
void FilterByType(Log* logs, int size, LogType filterType) {
	std::cout << "Logs of type " << LogTypeToString(filterType) << ":\n";
	for (int i = 0; i < size; i++) {
		if (logs[i].type == filterType) {
			logs[i].print();
		}
	}
}
bool IsValidTime(int h, int m, int s)
{
	return (h >= 0 && h < 24) &&
		(m >= 0 && m < 60) &&
		(s >= 0 && s < 60);
}
int main()
{
	int n;
	std::cin >> n;
	Log* logs = new Log[n];

	for (int i = 0; i < n; i++) {
		char time[9];
		char typeChar;

		std::cin >> time >> typeChar;
		std::cin.ignore();
		std::cin.getline(logs[i].message, MAX_MESSAGE);

		int h = (time[0] - '0') * 10 + (time[1] - '0');
		int m = (time[3] - '0') * 10 + (time[4] - '0');
		int s = (time[6] - '0') * 10 + (time[7] - '0');

		if (!IsValidTime(h, m, s)) {
			std::cout << "Invalid time, try again!\n";
			i--;
			continue;
		}

		logs[i].hours = h;
		logs[i].minutes = m;
		logs[i].seconds = s;

		logs[i].type = CharToLogType(typeChar);

		if (logs[i].type == Unknown) {
			std::cout << "Invalid type, try again!\n";
			i--;
			continue;
		}

		logs[i].calculate();
	}

	Statistic(logs, n);

	EarliestandLatest(logs, n);

	FilterByTime(logs, n, 3600, 7200);

	FilterByType(logs, n, Error);

	Sort(logs, n);
	std::cout << "\n--- Logs sorted by time ---\n";
	for (int i = 0; i < n; i++) {
		logs[i].print();
	}

	delete[] logs;
}