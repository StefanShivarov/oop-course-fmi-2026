#include <iostream>

using std::cin;
using std::cout;

struct Time {
    int hours, minutes, seconds;
};

struct LogRecord {
    Time time;
    char type;
    char message[100];

    void readLog() {
        char seperator;
        cin >> time.hours >> seperator >> time.minutes >> seperator >> time.seconds;
        cin >> type;
        cin.ignore();
        cin.getline(message, 100);
    }
};

void swap(LogRecord& log1, LogRecord& log2) {
    LogRecord temp = log1;
    log1 = log2;
    log2 = temp;
}

bool isLater(Time t1, Time t2) {
    if (t1.hours != t2.hours) {
        return t1.hours > t2.hours;
    }
    if (t1.minutes != t2.minutes) {
        return t1.minutes > t2.minutes;
    }
    if (t1.seconds != t2.seconds) {
        return t1.seconds > t2.seconds;
    }
    else {
        return true;
    }
}

void sortLogTime(LogRecord* log, int N) {
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if (isLater(log[j].time, log[j + 1].time)) {
                swap(log[j], log[j + 1]);
            }
        }
    }
}

void statisticType(LogRecord* log, int N) {
    unsigned countI = 0;
    unsigned countW = 0;
    unsigned countE = 0;
    unsigned countD = 0;

    for (int i = 0; i < N; i++)
    {
        if (log[i].type == 'I') {
            countI++;
        }
        else if (log[i].type == 'W') {
            countW++;
        }
        else if (log[i].type == 'E') {
            countE++;
        }
        else if (log[i].type == 'D') {
            countD++;
        }
    }

    cout << "Statistic - TYPE: " << '\n';
    cout << "Info: " << countI << '\n';
    cout << "Warn: " << countW << '\n';
    cout << "Error: " << countE << '\n';
    cout << "Debug: " << countD << '\n';
}

void printLogRecord(LogRecord log) {
    cout << log.time.hours << ":" << log.time.minutes << ":" << log.time.seconds << " ";
    cout << log.type << " ";
    cout << log.message;
}

void earliestAndLatestLog(LogRecord* log, int N) {
    LogRecord earliest = log[0];
    LogRecord latest = log[N-1];

    cout << "Earliest log Record: ";
    printLogRecord(earliest);
    cout << '\n';

    cout << "Latest log Record: ";
    printLogRecord(latest);
    cout << '\n';
}

void filterByTime(LogRecord* log, int N, Time t1, Time t2) {
    cout << "Logs between time interval: " << '\n';
    for (int i = 0; i < N; i++)
    {
        if (isLater(log[i].time,t1) && isLater(t2, log[i].time)) {
            printLogRecord(log[i]);
            cout << '\n';
        }
    }
}

void filterByType(LogRecord* log, int N, char targetType) {
    for (int i = 0; i < N; i++)
    {
        if (log[i].type == targetType) {
            printLogRecord(log[i]);
            cout << '\n';
        }
    }
}

int main()
{
    int N;
    std::cin >> N;
    LogRecord log;

    LogRecord* myLogs = new LogRecord[N];

    for (int i = 0; i < N; i++)
    {
        myLogs[i].readLog();
    }

    sortLogTime(myLogs, N);
    cout << '\n';
    for (int i = 0; i < N; i++)
    {
        printLogRecord(myLogs[i]);
        cout << '\n';
    }
    cout << '\n';
    statisticType(myLogs, N);
    cout << '\n';

    earliestAndLatestLog(myLogs, N);

    cout << '\n';
    Time t1 = { 10, 22, 33 }; 
    Time t2 = { 15, 45, 11 };
    filterByTime(myLogs, N, t1, t2);

    delete[]myLogs;
}
