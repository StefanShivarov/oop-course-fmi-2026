#include <iostream>
#include <cstring>
using namespace std;

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}
int IntegerParseInt(string input) {
    int result = 0;
    int len = input.length();
    for (int i = 0; i < len; i++) {
        result = result * 10 + input[i] - '0';
    }
    return result;
}
bool isValidTime(string time) {
    if (!isDigit(time[0]) || !isDigit(time[1]) || time[2] != ':' || !isDigit(time[3]) || !isDigit(time[4]) || time[5] != ':' || !isDigit(time[6]) || !isDigit(time[7])) {
        return false;
    }
    string hours;
    hours += time[0];
    hours += time[1];

    string minutes;
    minutes += time[3];
    minutes += time[4];

    string seconds;
    seconds += time[6];
    seconds += time[7];
    int hour = IntegerParseInt(hours);
    int minute = IntegerParseInt(minutes);
    int second = IntegerParseInt(seconds);
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
        return false;
    }
    return true;
}
enum LogType {
    Info,
    Warn,
    Error,
    Debug
};
struct Log {
    string time;
    char type{};
    string message;
    void toString() const {
        cout << time << " " << type << " " << message << endl;
    }
    bool isValid() const {
        if (!isValidTime(time)) {
            return false;
        }
        if (type != 'I' && type != 'W' && type != 'E' && type != 'D') {
            return false;
        }
        if (message == "") {
            return false;
        }
        return true;
    }
};
void swap(Log& a, Log& b) {
    Log temp = a;
    a = b;
    b = temp;
}
void bubbleSort(Log* logs, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (logs[j].time > logs[j + 1].time) {
                swap(logs[j], logs[j + 1]);
            }
        }
    }
}
int main() {
    int n;
    cin >> n;
    if (n < 1) {
        cout << "Invalid input" << endl;
        return 0;
    }
    Log* logs = new Log[n];
    for (int i = 0; i < n; i++) {
        cin >> logs[i].time;
        cin >> logs[i].type;
        cin >> logs[i].message;
        if (!logs[i].isValid()) {
            cout << "Invalid input" << endl;
            i--;
        }
    }
    int command;
    cout << "Choose option:" << endl;
    cout << "1. Sort logs by time" << endl;
    cout << "2. Log stats for every type" << endl;
    cout << "3. Earliest and latest log" << endl;
    cout << "4. Filter logs by interval" << endl;
    cout << "5. Filter logs by type" << endl;
    do {
        cin >> command;
        switch (command) {
            case 1:
                bubbleSort(logs, n);
                for (int i = 0; i < n; i++) {
                    logs[i].toString();
                }
                break;
            case 2: {
                int log_stats[4]{0};
                const char* logTypeNames[] = { "Info", "Warn", "Error", "Debug" };
                for (int i = 0; i < n; i++) {
                    if (logs[i].type == 'I') {
                        log_stats[Info]++;
                    }
                    else if (logs[i].type == 'W') {
                        log_stats[Warn]++;
                    }
                    else if (logs[i].type == 'E') {
                        log_stats[Error]++;
                    }
                    else if (logs[i].type == 'D') {
                        log_stats[Debug]++;
                    }
                }
                for (int i = 0; i < 4; i++) {
                    if (log_stats[i]) {
                        cout << logTypeNames[i] << ": " << log_stats[i] << endl;
                    }
                }
                break;
            }
            case 3:
                bubbleSort(logs, n);
                logs[0].toString();
                logs[n - 1].toString();
                break;
            case 4: {
                cout << "Enter begin and end time intervals:" << endl;
                string interval1, interval2;
                cin >> interval1 >> interval2;
                if (isValidTime(interval1) && isValidTime(interval2)) {
                    for (int i = 0; i < n; i++) {
                        if (logs[i].time >= interval1 && logs[i].time <= interval2) {
                            logs[i].toString();
                        }
                    }
                }
                else {
                    cout << "Invalid input" << endl;
                }
                break;
            }
            case 5: {
                int log_stats[4]{0};
                const char* logTypeNames[] = { "Info", "Warn", "Error", "Debug" };
                for (int i = 0; i < n; i++) {
                    if (logs[i].type == 'I') {
                        log_stats[Info]++;
                    }
                    else if (logs[i].type == 'W') {
                        log_stats[Warn]++;
                    }
                    else if (logs[i].type == 'E') {
                        log_stats[Error]++;
                    }
                    else if (logs[i].type == 'D') {
                        log_stats[Debug]++;
                    }
                }
                for (int i = 0; i < 4; i++) {
                    if (log_stats[i]) {
                        cout << logTypeNames[i] << ": " << endl;
                        for (int j = 0; j < n; j++) {
                            if ((logs[j].type == 'I' && i == Info) || (logs[j].type == 'W' && i == Warn) || (logs[j].type == 'E' && i == Error) || (logs[j].type == 'D' && i == Debug)) {
                                logs[j].toString();
                            }
                        }
                    }
                }
                break;
            }
        }
    }
    while (command >= 1 && command <= 5);
    delete[] logs;
}