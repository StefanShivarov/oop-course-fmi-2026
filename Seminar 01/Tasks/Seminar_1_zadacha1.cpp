

#include <iostream>

using std::cin;
using std::cout;


//ZADACHA 1
namespace Logs {

    const int MAX_LENGTH = 100;
    const int EXPECTED_LENGTH = 9;

    enum class TYPE {
        I,
        W,
        E,
        D
    };

    struct Time {
        int hours;
        int minutes;
        int seconds;
    };

    struct Log {
        Time time;
        TYPE type;
        char message[MAX_LENGTH];
    };

    bool isDigit(const char c) {
        return c >= '0' && c <= '9';
    }

    bool isValidTimeFormat(const char* str) {
        if (!str) return false;

        for (int i = 0; i < EXPECTED_LENGTH - 1; i++) {
            if (i == 2 || i == 5) {
                if (str[i] != ':') return false;
            }
            else {
                if (!isDigit(str[i])) return false;
            }
        }

        return str[8] == '\0';
    }

    bool isValidTimeValues(int h, int m, int s) {
        return (h >= 0 && h <= 23) &&
            (m >= 0 && m <= 59) &&
            (s >= 0 && s <= 59);
    }

    bool isValidType(char c) {
        return c == 'I' || c == 'W' || c == 'E' || c == 'D';
    }

    bool isEmptyString(const char* str) {
        if (!str) return true;
        return str[0] == '\0';
    }

    int timeToSeconds(const Time& t) {
        return t.hours * 3600 + t.minutes * 60 + t.seconds;
    }

    bool isEarlier(const Log& a, const Log& b) {
        return timeToSeconds(a.time) < timeToSeconds(b.time);
    }

    TYPE charToType(char c) {
        switch (c) {
        case 'I':
            return TYPE::I;
        case 'W':
            return TYPE::W;
        case 'E':
            return TYPE::E;
        case 'D':
            return TYPE::D;
        }
    }

    char typeToChar(TYPE t) {
        switch (t) {
        case TYPE::I:
            return 'I';
        case TYPE::W:
            return 'W';
        case TYPE::E:
            return 'E';
        case TYPE::D:
            return 'D';
        }
    }


    void printLog(const Log& log) {
        if (log.time.hours < 10) cout << "0";
        cout << log.time.hours << ":";

        if (log.time.minutes < 10) cout << "0";
        cout << log.time.minutes << ":";

        if (log.time.seconds < 10) cout << "0";
        cout << log.time.seconds << " ";

        cout << typeToChar(log.type) << " ";
        cout << log.message << "\n";
    }

    void sortLogs(Log logs[], int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (isEarlier(logs[j + 1], logs[j])) {
                    Log temp = logs[j];
                    logs[j] = logs[j + 1];
                    logs[j + 1] = temp;
                }
            }
        }
    }

    void printStatistics(Log logs[], int n) {
        int countI = 0, countW = 0, countE = 0, countD = 0;

        for (int i = 0; i < n; i++) {
            switch (logs[i].type) {
            case TYPE::I:
                countI++;
                break;
            case TYPE::W:
                countW++;
                break;
            case TYPE::E:
                countE++; 
                break;
            case TYPE::D:
                countD++;
                break;
            }
        }

        cout << "Info: " << countI << "\n";
        cout << "Warn: " << countW << "\n";
        cout << "Error: " << countE << "\n";
        cout << "Debug: " << countD << "\n";
    }

    void printEarliestAndLatest(Log logs[], int n) {
        if (n == 0) return;

        int minIndex = 0;
        int maxIndex = 0;

        for (int i = 1; i < n; i++) {
            if (isEarlier(logs[i], logs[minIndex]))
                minIndex = i;

            if (isEarlier(logs[maxIndex], logs[i]))
                maxIndex = i;
        }

        cout << "Earliest:\n";
        printLog(logs[minIndex]);

        cout << "Latest:\n";
        printLog(logs[maxIndex]);
    }

    void filterByTime(Log logs[], int n, Time t1, Time t2) {
        int start = timeToSeconds(t1);
        int end = timeToSeconds(t2);

        for (int i = 0; i < n; i++) {
            int current = timeToSeconds(logs[i].time);
            if (current >= start && current <= end) {
                printLog(logs[i]);
            }
        }
    }

    void filterByType(Log logs[], int n, TYPE type) {
        for (int i = 0; i < n; i++) {
            if (logs[i].type == type) {
                printLog(logs[i]);
            }
        }
    }

}

int main() {
    using namespace Logs;

    int n;
    cin >> n;
    if (n <= 0) {
        cout << "Invalid number of logs\n";
        return -1;
    }

    Log* logs = new Log[n];

    for (int i = 0; i < n; i++) {

        char timeStr[9];
        char typeChar;

        cin >> timeStr >> typeChar;
        cin.ignore();
        cin.getline(logs[i].message, MAX_LENGTH);

        if (!isValidTimeFormat(timeStr)) {
            delete[] logs;
            return -1;
        }

        int hours = (timeStr[0] - '0') * 10 + (timeStr[1] - '0');
        int minutes = (timeStr[3] - '0') * 10 + (timeStr[4] - '0');
        int seconds = (timeStr[6] - '0') * 10 + (timeStr[7] - '0');

        if (!isValidTimeValues(hours, minutes, seconds)) {
            delete[] logs;
            return -1;
        }

        logs[i].time.hours = hours;
        logs[i].time.minutes = minutes;
        logs[i].time.seconds = seconds;

        if (!isValidType(typeChar)) {
            delete[] logs;
            return -1;
        }

        logs[i].type = charToType(typeChar);

        if (isEmptyString(logs[i].message)) {
            delete[] logs;
            return -1;
        }
    }

    cout << "--- Sorted logs ---\n";
    sortLogs(logs, n);
    for (int i = 0; i < n; i++)
        printLog(logs[i]);

    cout << "--- Statistics ---\n";
    printStatistics(logs, n);

    cout << "--- Earliest and Latest ---\n";
    printEarliestAndLatest(logs, n);

    delete[] logs;

    return 0;
}