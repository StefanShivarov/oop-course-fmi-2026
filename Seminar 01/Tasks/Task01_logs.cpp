#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;

namespace Constants {
    const int MAX_MESSAGE_LENGTH = 51;
}

struct Timestamp {
    int hour = 0;
    int minutes = 0;
    int seconds = 0;
};

enum class LogType {
    INFO, WARN, ERROR, DEBUG
};

struct Log {
    Timestamp timestamp;
    LogType type = LogType::INFO;
    char message[Constants::MAX_MESSAGE_LENGTH] = "";
};

namespace utils {
    Timestamp parseTimestampFromString(const char* str) {
        size_t length = strlen(str);
        if (length != 8 || str[2] != ':' || str[5] != ':') {
            // throw some exception
            return {};
        }
        int hours = (str[0] - '0') * 10 + (str[1] - '0');
        if (hours > 23) { return {}; }
        int minutes = (str[3] - '0') * 10 + (str[4] - '0');
        if (minutes > 59) { return {}; }
        int seconds = (str[6] - '0') * 10 + (str[7] - '0');
        if (seconds > 59) { return {}; }
        return { hours, minutes, seconds };
    }

    LogType parseLogTypeFromString(const char* str) {
        if (strcmp(str, "INFO") == 0) {
            return LogType::INFO;
        }
        if (strcmp(str, "WARN") == 0) {
            return LogType::WARN;
        }
        if (strcmp(str, "ERROR") == 0) {
            return LogType::ERROR;
        }
        if (strcmp(str, "DEBUG") == 0) {
            return LogType::DEBUG;
        }
        return LogType::INFO;
    }

    const char* convertLogTypeToString(LogType type) {
        switch (type) {
            case LogType::INFO: return "INFO";
            case LogType::WARN: return "WARN";
            case LogType::ERROR: return "ERROR";
            case LogType::DEBUG: return "DEBUG";
            default: return "INFO";
        }
    }

    void writeTimestamp(const Timestamp& t, ostream& out) {
        if (t.hour < 10) {
            out << '0';
        }
        out << t.hour << ':';

        if (t.minutes < 10) {
            out << '0';
        }
        out << t.minutes << ':';

        if (t.seconds < 10) {
            out << '0';
        }
        out << t.seconds;
    }

    int convertTimestampToSeconds(const Timestamp& t) {
        return t.hour * 3600 + t.minutes * 60 + t.seconds;
    }

    int compareTimestamps(const Timestamp& t1, const Timestamp& t2) {
        int firstSeconds = convertTimestampToSeconds(t1);
        int secondSeconds = convertTimestampToSeconds(t2);
        if (firstSeconds > secondSeconds) {
            return 1;
        }
        if (firstSeconds < secondSeconds) {
            return -1;
        }
        return 0;
    }

}

void readLog(Log& log, istream& is = cin) {
    char buff[10];
    is >> buff;

    log.timestamp = utils::parseTimestampFromString(buff);
    buff[0] = '\0';

    is >> buff;
    log.type = utils::parseLogTypeFromString(buff);

    is.ignore();
    is.getline(log.message, Constants::MAX_MESSAGE_LENGTH);
}

void writeLog(const Log& log, ostream& os = cout) {
    utils::writeTimestamp(log.timestamp, os);
    os << ' ' << utils::convertLogTypeToString(log.type);
    os << ' ' << log.message << '\n';
}

void sortLogs(Log* logs, size_t logsCount, bool (*comparator)(const Log&, const Log&)) {
    for (int i = 0; i < logsCount; i++) {
        int minIndex = i;
        for (int j = i + 1; j < logsCount; j++) {
            if (comparator(logs[j], logs[minIndex])) {
                minIndex = j;
            }
        }

        if (i != minIndex) {
            std::swap(logs[i], logs[minIndex]);
        }
    }
}

void filterLogs(const Log* logs, size_t logsCount, bool (*shouldPrint)(const Log&), ostream& os = cout) {
    for (int i = 0; i < logsCount; i++) {
        if (shouldPrint(logs[i])) {
            writeLog(logs[i], os);
        }
    }
}

void writeAllLogs(const Log* logs, size_t logsCount) {
    filterLogs(logs, logsCount, [](const Log& log) { return true; });
}

void printCountsByLogType(const Log* logs, size_t logsCount) {
    int logTypeCounts[4] {0};
    for (int i = 0; i < logsCount; i++) {
        logTypeCounts[(int)logs[i].type]++;
    }
    for (int i = 0; i <= 3; i++) {
        cout << utils::convertLogTypeToString((LogType) i) << ": " << logTypeCounts[i] << '\n';
    }
}

void printEarliestLog(Log* logs, size_t logsCount) {
    sortLogs(logs, logsCount, [](const Log& l1, const Log& l2) { return utils::compareTimestamps(l1.timestamp, l2.timestamp) < 0; });
    writeLog(logs[0]);
}

void printLatestLog(Log* logs, size_t logsCount) {
    sortLogs(logs, logsCount, [](const Log& l1, const Log& l2) { return utils::compareTimestamps(l1.timestamp, l2.timestamp) < 0; });
    writeLog(logs[logsCount - 1]);
}

int main() {
    int n;
    cin >> n;

    Log* logs = new Log[n];
    for (int i = 0; i < n; i++) {
        readLog(logs[i]);
    }

    cout << "Sort by timestamp\n";
    sortLogs(logs, n, [](const Log& l1, const Log& l2) { return utils::compareTimestamps(l1.timestamp, l2.timestamp) < 0; });
    writeAllLogs(logs, n);

    cout << "Filter logs in interval\n";
    filterLogs(logs, n, [](const Log& log) {
        return utils::compareTimestamps(log.timestamp, {12, 30, 0 }) >= 0 && utils::compareTimestamps(log.timestamp, {17, 0, 0 }) <= 0;
    });

    cout << "Earliest log\n";
    printEarliestLog(logs, n);

    cout << "Latest log\n";
    printLatestLog(logs, n);

    cout << "Logs by type\n";
    printCountsByLogType(logs, n);

    cout << "Filter logs by type\n";
    filterLogs(logs, n, [](const Log& log) { return log.type == LogType::INFO; });

    delete[] logs;
}
