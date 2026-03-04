#include <iostream>
const int MAX_Text = 11;
bool StrCompare(const char* str1, const char* str2) {
	int i = 0;
	while (str1[i] != '\0' && str2[i] != '\0') {
		if (str1[i] != str2[i]) {
			return false;
		}
		i++;
	}
	return str1[i] == '\0' && str2[i] == '\0';
}
void StrCopy(char* dest, const char* src) {
	int i = 0;
	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
enum ProblemType
{
	Engine,
	Brakes,
	Tires,
	Gearbox,
	Suspension,
	Other,
	Unknown
};
ProblemType CharToProblemType(char c)
{
	switch (c)
	{
	case 'E': return Engine;
	case 'B': return Brakes;
	case 'T': return Tires;
	case 'G': return Gearbox;
	case 'S': return Suspension;
	case 'O': return Other;
	default:  return Unknown;
	}
}
char ProblemTypeToChar(ProblemType t)
{
	switch (t)
	{
	case Engine:     return 'E';
	case Brakes:     return 'B';
	case Tires:      return 'T';
	case Gearbox:    return 'G';
	case Suspension: return 'S';
	case Other:      return 'O';
	default:         return '?';
	}
}
struct ServiceLog
{
	char registration[MAX_Text]{ '\0' };
	ProblemType type = Unknown;
	int emergencyLevel = 1;
	char progress[MAX_Text]{ "Waiting" };

	void print() const {
		std::cout << registration << " "
			<< ProblemTypeToChar(type) << " "
			<< emergencyLevel << " "
			<< progress << "\n";
	}

	void StartWork() {
		if (StrCompare(progress, "Waiting")) {
			StrCopy(progress, "InProgress");
		}
	}

	void CompleteWork() {
		if (StrCompare(progress, "InProgress")) {
			StrCopy(progress, "Done");
		}
	}
};

void FilterByProgress(const ServiceLog* logs, int size, const char* progress) {
	std::cout << "Filtered by progress: " << progress << "\n";
	for (int i = 0; i < size; i++) {
		if (StrCompare(logs[i].progress, progress)) {
			std::cout << logs[i].registration << " " << logs[i].type << " " << logs[i].emergencyLevel << " " << logs[i].progress << "\n";
		}
	}
}
void SortByEmergencyLevel(ServiceLog* logs, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (logs[j].emergencyLevel > logs[j + 1].emergencyLevel) {
				ServiceLog temp = logs[j + 1];
				logs[j + 1] = logs[j];
				logs[j] = temp;
			}
		}
	}
}
void PrintWaitingLogs(const ServiceLog* logs, int size) {
	int count = 0;
	std::cout << "Waiting logs:\n";
	for (int i = 0; i < size; i++) {
		if (StrCompare(logs[i].progress, "Waiting")) {
			count++;
		}
	}
	ServiceLog* waitingLogs = new ServiceLog[count]{};
	int index = 0;
	for (int i = 0; i < size; i++) {
		if (StrCompare(logs[i].progress, "Waiting")) {
			waitingLogs[index++] = logs[i];
		}
	}
	SortByEmergencyLevel(waitingLogs, count);
	for (int i = 0; i < count; i++) {
		waitingLogs[i].print();
	}
}
void FilterByType(const ServiceLog* logs, int size, ProblemType type) {
	std::cout << "Filtered by type: " << ProblemTypeToChar(type) << "\n";
	for (int i = 0; i < size; i++) {
		if (logs[i].type == type) {
			logs[i].print();
		}
	}
}
int FindByRegistration(ServiceLog* logs, int size, const char* reg) {
	for (int i = 0; i < size; i++) {
		if (StrCompare(logs[i].registration, reg)) {
			return i;
		}
	}
	return -1;
}
int main()
{
	int n;
	std::cin >> n;

	ServiceLog* logs = new ServiceLog[n]{};

	for (int i = 0; i < n; i++) {
		char typeChar;
		int elevel;
		char progress[MAX_Text]{ '\0' };

		std::cin >> logs[i].registration >> typeChar >> elevel >> progress;

		ProblemType pType = CharToProblemType(typeChar);

		if (pType == Unknown ||
			elevel < 1 || elevel > 5 ||
			!(StrCompare(progress, "Waiting") ||
				StrCompare(progress, "InProgress") ||
				StrCompare(progress, "Done")))
		{
			i--;
			continue;
		}

		logs[i].type = pType;
		logs[i].emergencyLevel = elevel;
		StrCopy(logs[i].progress, progress);
	}
	FilterByProgress(logs, n, "Waiting");
	std::cout << "\n";

	char regStart[MAX_Text];
	std::cin >> regStart;
	int index = FindByRegistration(logs, n, regStart);
	if (index != -1) {
		logs[index].StartWork();
	}
	char regDone[MAX_Text];
	std::cin >> regDone;

	index = FindByRegistration(logs, n, regDone);
	if (index != -1) {
		logs[index].CompleteWork();
	}
	PrintWaitingLogs(logs, n);
	std::cout << "\n";

	char filterTypeChar;
	std::cin >> filterTypeChar;
	ProblemType filterType = CharToProblemType(filterTypeChar);

	if (filterType != Unknown)
	{
		FilterByType(logs, n, filterType);
	}

	delete[] logs;
}