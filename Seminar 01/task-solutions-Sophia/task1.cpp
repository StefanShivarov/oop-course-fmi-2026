#include <iostream>
using std::cout;
using std::cin;

enum LogType {
    INFO,
    WARN,
    ERROR,
    DEBUG
};

struct Log {
    char time[9];
    LogType type;
    char message[256];
};

int timeToSeconds(const char time[]) {
    int h = (time[0] - '0') * 10 + (time[1] - '0');
    int m = (time[3] - '0') * 10 + (time[4] - '0');
    int s = (time[6] - '0') * 10 + (time[7] - '0');
    return h * 3600 + m * 60 + s;
}

char* secondsToTime(int seconds, char time[]) {
    int h = seconds / 3600;
    int m = (seconds % 3600) / 60;
    int s = seconds % 60;
    time[0] = (h / 10) + '0';
    time[1] = (h % 10) + '0';
    time[2] = ':';
    time[3] = (m / 10) + '0';
    time[4] = (m % 10) + '0';
    time[5] = ':';
    time[6] = (s / 10) + '0';
    time[7] = (s % 10) + '0';
    time[8] = '\0';
    return time;
}

char logTypeToChar(LogType type) {
    switch (type) {
        case INFO: return 'I';
        case WARN: return 'W';
        case ERROR: return 'E';
        case DEBUG: return 'D';
        default: return 'I';
    }
}

bool isValidTime(const char* time) {
    if (time[2] != ':' || time[5] != ':') return false;
    int h = (time[0] - '0') * 10 + (time[1] - '0');
    int m = (time[3] - '0') * 10 + (time[4] - '0');
    int s = (time[6] - '0') * 10 + (time[7] - '0');
    if (h < 0 || h > 23) return false;
    if (m < 0 || m > 59) return false;
    if (s < 0 || s > 59) return false;
    return true;
}

bool isValidLogType(char type) {
    if (type == 'I') return true;
    if (type == 'E') return true;
    if (type == 'W') return true;
    if (type == 'D') return true;
    return false;
}

void readLog(Log& log) {
    cout << "Enter log time (HH:MM:SS): \n";
    
    do {
        cin.getline(log.time, 9);
    }
    while (!isValidTime(log.time));

    cout << "Enter log type (I/W/E/D): \n";
    char logType;
    do {
        cin >> logType;
    }
    while (!isValidLogType(logType));

    switch (logType) {
        case 'I': log.type = INFO; break;
        case 'W': log.type = WARN; break;
        case 'E': log.type = ERROR; break;
        case 'D': log.type = DEBUG; break;
        default: log.type = INFO; break;
    }

    cin.ignore();
    cout << "Enter log message: \n";
    cin.getline(log.message, 256);
}

void printLog(const Log& log) {
    cout << log.time << " " << logTypeToChar(log.type) << " " << log.message << "\n";
}

int oldestLog(Log* logs, int N) {
    int min = timeToSeconds(logs[0].time);
    for (int i = 1; i < N; i++) {
        int current = timeToSeconds(logs[i].time);
        if (current < min) {
            min = current;
        }
    }
    return min;
}

int newestLog(Log* logs, int N) {
    int max = timeToSeconds(logs[0].time);
    for (int i = 1; i < N; i++) {
        int current = timeToSeconds(logs[i].time);
        if (current > max) {
            max = current;
        }
    }
    return max;
}

void statsForTypeOfLog(Log* logs, int N) {
    int counterI = 0;
    int counterW = 0;
    int counterE = 0;
    int counterD = 0;
    for (int i = 0; i < N; i++) {
        if (logTypeToChar(logs[i].type) == 'I') {
            counterI++;
        }
        else if (logTypeToChar(logs[i].type) == 'W') {
            counterW++;
        }
        else if (logTypeToChar(logs[i].type) == 'E') {
            counterE++;
        }
        else if (logTypeToChar(logs[i].type) == 'D') {
            counterD++;
        }
    }
    cout << "INFO: " << counterI << "\n";
    cout << "WARN: " << counterW << "\n";
    cout << "ERROR: " << counterE << "\n";
    cout << "DEBUG: " << counterD << "\n";
}

void sortLogsByTime(Log* logs, int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (timeToSeconds(logs[j].time) > timeToSeconds(logs[j + 1].time)) {
                Log temp = logs[j];
                logs[j] = logs[j + 1];
                logs[j + 1] = temp;
            }
        }
    }
}

void filterByType(Log* logs, int N, LogType wantedType) {
    for (int i = 0; i < N; i++) {
        if (logs[i].type == wantedType) {
            printLog(logs[i]);
        }
    }
}

void filterByTimeInterval(Log* logs, int N, const char* startTime, const char* endTime) {
    int startSeconds = timeToSeconds(startTime);
    int endSeconds = timeToSeconds(endTime);
    for (int i = 0; i < N; i++) {
        int logSeconds = timeToSeconds(logs[i].time);
        if (logSeconds >= startSeconds && logSeconds <= endSeconds) {
            printLog(logs[i]);
        }
    }
}

int main() {
    int N;
    char timeBuffer[9];
    cout << "Enter number of logs: \n";
    do {
        cin >> N;
    } 
    while (N <= 0);
    cin.ignore();
    Log* logs = new Log[N];

    for (int i = 0; i < N; i++) {
        cout << "\nLog " << i + 1 << ":\n";
        readLog(logs[i]);
    }
    
    cout << "Enter a inverval of time (start and end) to filter logs (HH:MM:SS): \n";
    char startTime[9], endTime[9];
    
    do {
        cin.getline(startTime, 9);
    }
    while (!isValidTime(startTime));
    do {
        cin.getline(endTime, 9);
    }
    while (!isValidTime(endTime));


    cout << "\nEnter a type of log to filter (I/W/E/D): \n";
    char typeChar;
    cin >> typeChar;
    LogType wantedType;

    switch (typeChar) {
        case 'I': wantedType = INFO; break;
        case 'W': wantedType = WARN; break;
        case 'E': wantedType = ERROR; break;
        case 'D': wantedType = DEBUG; break;
        default: wantedType = INFO; break;
    }

    cout << "\nSorted logs ascending by time:\n";
    sortLogsByTime(logs, N);
    for (int i = 0; i < N; i++) {
        printLog(logs[i]);
    }

    cout << "\nStats for type of log:\n";
    statsForTypeOfLog(logs, N);

    secondsToTime(oldestLog(logs, N), timeBuffer);
    cout << "\nOldest log time: " << timeBuffer << "\n";
    secondsToTime(newestLog(logs, N), timeBuffer);
    cout << "Newest log time: " << timeBuffer << "\n";

    cout << "\nFilter by time interval (" << startTime << " - " << endTime << "):\n";
    filterByTimeInterval(logs, N, startTime, endTime);

    cout << "\nFilter by type (" << logTypeToChar(wantedType) << "):\n";
    filterByType(logs, N, wantedType);

    delete[] logs;
    return 0;
}