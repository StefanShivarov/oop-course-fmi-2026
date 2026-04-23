#include <iostream>

using std::cin;
using std::cout;

namespace Logs {

    namespace Constants {
        const int MAX_MESSAGE = 256;
        const char SYMBOL = ':';
		const char ZERO = '0';
        const int TIME_SIZE = 9;
    }
    struct Time {
        int h;
        int m;
        int s;
    };

    enum class LogType {
        INFO, WARNING, ERROR, DEBUG, UNKNOWN
    };

    using namespace Constants;

    struct LogEntry {
        Time time;
        LogType type;
        char message[MAX_MESSAGE];
    };


    Time parseTime(const char* str) {
        Time t;
        if (str == nullptr) return {};
   
        t.h = (str[0] - '0') * 10 + (str[1] - '0');
        t.m = (str[3] - '0') * 10 + (str[4] - '0');
        t.s = (str[6] - '0') * 10 + (str[7] - '0');
        return t;
    }
    LogType parseType(char c) {
        switch (c) {
        case 'I': return LogType::INFO;
        case 'W': return LogType::WARNING;
        case 'E': return LogType::ERROR;
        case 'D': return LogType::DEBUG;
        default:  return LogType::UNKNOWN;
        }
    }
    const char* getTypeName(LogType t) {
        switch (t) {
        case LogType::INFO: return "INFO";
        case LogType::WARNING: return "WARNING";
        case LogType::ERROR: return "ERROR";
        case LogType::DEBUG: return "DEBUG";
        default: return "UNKNOWN";
        }
    }

    bool isEarlier(const Time& a, const Time& b) {
        if (a.h != b.h) return a.h < b.h;
        if (a.m != b.m) return a.m < b.m;
        return a.s < b.s;
    }

    void readLog(LogEntry& log) {
        char timeStr[9];
        char typeChar;

        cin >> timeStr >> typeChar;
        cin.ignore();

        cin.getline(log.message, MAX_MESSAGE);

        log.time = parseTime(timeStr);
        log.type = parseType(typeChar);
    }

    void printLog(const LogEntry& log) {
        if (log.time.h < 10) cout << ZERO;
        cout << log.time.h << SYMBOL;

        if (log.time.m < 10) cout << ZERO;
        cout << log.time.m << SYMBOL;

        if (log.time.s < 10) cout << '0';
        cout << log.time.s << " [" << getTypeName(log.type) << "] "
            << log.message << '\n';
    }

    void swap(LogEntry& a, LogEntry& b) {
        LogEntry temp = a;
        a = b;
        b = temp;
	}
    void sortLogsBytime(LogEntry* logs, int n) {
        for (int i = 0; i < n-1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (isEarlier(logs[j].time, logs[minIdx].time)) {
                    minIdx = j;
                }
            }
            if (i != minIdx) swap(logs[i], logs[minIdx]);
        }
    }

    void printStats(const LogEntry* logs, int n) {

        int counts[4] = { 0 };

        for (int i = 0; i < n; i++) {
            switch (logs[i].type) {
            case LogType::INFO: counts[0]++; break;
            case LogType::WARNING: counts[1]++; break;
            case LogType::ERROR: counts[2]++; break;
            case LogType::DEBUG: counts[3]++; break;
            default: break;
            }
        }

        cout << "INFO: " << counts[0] << '\n';
        cout << "WARNING: " << counts[1] << '\n';
        cout << "ERROR: " << counts[2] << '\n';
        cout << "DEBUG: " << counts[3] << '\n';
    }

    void printFirstLast(const LogEntry* logs, int n) {
        if (n == 0) return;

        cout << "Earliest:\n";
        printLog(logs[0]);

        cout << "Latest:\n";
        printLog(logs[n - 1]);
    }

    bool inInterval(const Time& t, const Time& a, const Time& b) {
        return !isEarlier(t, a) && !isEarlier(b, t);
    }
    void filterByTime(const LogEntry* logs, int n, Time t1, Time t2) {
        for (int i = 0; i < n; i++) {
            if (inInterval(logs[i].time, t1, t2)) {
                printLog(logs[i]);
            }
        }
    }

    void filterByType(const LogEntry* logs, int n, LogType type) {
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

    LogEntry* logs = new LogEntry[n];

    for (int i = 0; i < n; i++) {
        readLog(logs[i]);
    }

    sortLogsBytime(logs, n);

    cout << "\nAll logs sorted by time:\n";
    for (int i = 0; i < n; i++)
    {
        printLog(logs[i]);
    }

    cout << "\nStatistics:\n";
    printStats(logs, n);

    cout << "\nFirst and last:\n";
    printFirstLast(logs, n);

    char timeStr1[TIME_SIZE], timeStr2[TIME_SIZE];
    cout << "Enter time interval (hh:mm:ss hh:mm:ss): ";
    cin >> timeStr1 >> timeStr2;

    Time t1 = parseTime(timeStr1);
    Time t2 = parseTime(timeStr2);

    cout << "\nFiltered by time:\n";
    filterByTime(logs, n, t1, t2);


    cout << "\n Enter type";
	LogType type;
    char c;
    cin >> c;
	type = parseType(c);
    cout << "\nOnly this type:\n";
    filterByType(logs, n, type);

    delete[] logs;
}

