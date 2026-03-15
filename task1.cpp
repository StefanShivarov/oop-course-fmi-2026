#include <iostream>
#include <fstream>
using namespace std;

class Time {
    int hours;
    int minutes;
    int seconds;
    public:
        int getHours() const {
            return hours;
        }
        int getMinutes() const {
            return minutes;
        }
        int getSeconds() const {
            return seconds;
        }
        bool setHours(const int hours) {
            if (hours >= 0 && hours <= 23) {
                this -> hours = hours;
                return true;
            }
            return false;
        }
        bool setMinutes(const int minutes) {
            if (minutes >= 0 && minutes <= 59) {
                this -> minutes = minutes;
                return true;
            }
            return false;
        }
        bool setSeconds(const int seconds) {
            if (seconds >= 0 && seconds <= 59) {
                this -> seconds = seconds;
                return true;
            }
            return false;
        }
        int toSeconds() const {
            return hours * 60 * 60 + minutes * 60 + seconds;
        }
        void addSeconds(const int delta) {
            seconds += delta;
            while (seconds >= 60) {
                seconds -= 60;
                minutes++;
            }
            while (minutes >= 60) {
                minutes -= 60;
                hours++;
            }
            while (hours >= 24) {
                hours -= 24;
            }
        }
        bool isBefore(const Time& otherTime) const {
            if (this -> hours != otherTime.hours) {
                return this -> hours < otherTime.hours;
            }
            if (this -> minutes != otherTime.minutes) {
                return this -> minutes < otherTime.minutes;
            }
            if (this -> seconds != otherTime.seconds) {
                return this -> seconds < otherTime.seconds;
            }
            return true;
        }
        bool isAfter(const Time& otherTime) const {
            if (this -> hours != otherTime.hours) {
                return this -> hours > otherTime.hours;
            }
            if (this -> minutes != otherTime.minutes) {
                return this -> minutes > otherTime.minutes;
            }
            if (this -> seconds != otherTime.seconds) {
                return this -> seconds > otherTime.seconds;
            }
            return true;
        }
};
int strToInt(const string& str) {
    int res = 0;
    const size_t n = str.length();
    for (size_t i = 0; i < n; i++) {
        res = res * 10 + str[i] - '0';
    }
    return res;
}
void resize(Time*& arr, const size_t size) {
    Time* new_arr = new Time[size + 1];
    for (size_t i = 0; i < size; i++) {
        new_arr[i] = arr[i];
    }
    delete [] arr;
    arr = new_arr;
}
void selectionSort(Time arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].isBefore(arr[minIndex])) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}
int main() {
    ifstream ifs("times.txt");
    Time* arr = new Time[0];
    int n = 0;
    if (!ifs.is_open()) {
        println("File couldn't be open for reading!");
        delete[] arr;
        return 1;
    }
    int hours, minutes, seconds;
    while (!ifs.eof()) {
        resize(arr, n);
        ifs >> hours;
        ifs.ignore();
        ifs >> minutes;
        ifs.ignore();
        ifs >> seconds;
        Time t;
        t.setHours(hours);
        t.setMinutes(minutes);
        t.setSeconds(seconds);
        arr[n++] = t;
    }
    ifs.close();
    selectionSort(arr, n);
    ofstream ofs("times.txt");
    if (!ofs.is_open()) {
        println("File couldn't be open for writing!");
        delete[] arr;
        return 1;
    }
    ofs.trunc;
    for (int i = 0; i < n; i++) {
        println(ofs,"{:02}:{:02}:{:02}" , arr[i].getHours(), arr[i].getMinutes(), arr[i].getSeconds());
    }
    ofs.close();
    delete[] arr;
}