#include <iostream>
#include <fstream>
#include <print>

using std::ostream;
using std::istream;
using std::cin;
using std::cout;
using std::println;
using std::swap;

class Time {
private:
    unsigned hours = 0;
    unsigned minutes = 0;
    unsigned seconds = 0;

    mutable bool validTotalSeconds = false;
    mutable unsigned totalSeconds = 0;

    void recalculate() {
        hours = totalSeconds / 3600;
        minutes = (totalSeconds % 3600) / 60;
        seconds = totalSeconds % 60;
        validTotalSeconds = true;
    }

public:
    unsigned toSeconds() const {
        if (validTotalSeconds) {
            return totalSeconds;
        }

        totalSeconds = seconds + minutes * 60 + hours * 3600;
        validTotalSeconds = true;
        return totalSeconds;
    }

    void addSeconds(int secondsDelta) {
        totalSeconds = this->toSeconds();
        totalSeconds += secondsDelta;
        recalculate();
    }

    bool isBefore(const Time& other) const {
        return this->toSeconds() < other.toSeconds();
    }

    bool isAfter(const Time& other) const {
        return this->toSeconds() > other.toSeconds();
    }

    unsigned getHours() const {
        return hours;
    }

    unsigned getMinutes() const {
        return minutes;
    }

    unsigned getSeconds() const {
        return seconds;
    }

    bool setHours(unsigned hours) {
        if (hours > 23) {
            return false;
        }
        this->hours = hours;
        validTotalSeconds = false;
        return true;
    }

    bool setMinutes(unsigned minutes) {
        if (minutes > 59) {
            return false;
        }
        this->minutes = minutes;
        validTotalSeconds = false;
        return true;
    }

    bool setSeconds(unsigned seconds) {
        if (seconds > 59) {
            return false;
        }
        this->seconds = seconds;
        validTotalSeconds = false;
        return true;
    }

};

bool readTime(Time& time, istream& is = cin) {
    unsigned h, m, s;
    char delimiter;
    is >> h >> delimiter;
    if (!time.setHours(h) || delimiter != ':') {
        return false;
    }
    is >> m >> delimiter;
    if (!time.setMinutes(m) || delimiter != ':') {
        return false;
    }
    is >> s;
    return time.setSeconds(s);
}

void writeTime(const Time& time, ostream& os = cout) {
    println(os, "{:02}:{:02}:{:02}",
        time.getHours(), time.getMinutes(), time.getSeconds());
}

void sortTimes(Time* times, size_t timesCount, bool (*comparator) (const Time&, const Time&)) {
    for (int i = 0; i < timesCount; i++) {
        int minIndex = i;
        for (int j = i + 1; j < timesCount; j++) {
            if (comparator(times[j], times[minIndex])) {
                minIndex = j;
            }
        }

        if (i != minIndex) {
            swap(times[i], times[minIndex]);
        }
    }
}

int main(){

    std::ifstream ifs("times.txt");
    if (!ifs.is_open()) {
        cout << "Error opening file!\n";
        return 1;
    }

    int n;
    ifs >> n;
    Time* times = new Time[n];
    for (int i = 0; i < n; i++) {
        readTime(times[i], ifs);
    }

    sortTimes(times, n, [](const Time& a, const Time& b) {
        return a.isBefore(b);
    });

    for (int i = 0; i < n; i++) {
        writeTime(times[i]);
    }
}
