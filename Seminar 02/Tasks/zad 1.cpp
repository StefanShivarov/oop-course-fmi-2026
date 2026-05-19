
#include <iostream>
#include <fstream>
#include <print>
using std::cout;

class Time 
{
    private:
        int hours = 0; 
        int minutes = 0; 
        int seconds = 0;

    public:
        bool setHours(int h) 
        {
            if (h < 0 || h > 23) return false;
            hours = h;
            return true;
        }

        bool setMinutes(int m) 
        {
            if (m < 0 || m > 59) return false;
            minutes = m;
            return true;
        }

        bool setSeconds(int s) 
        {
            if (s < 0 || s > 59) return false;
            seconds = s;
            return true;
        }

        bool setAll(int h, int m, int s) 
        {
            if (!setHours(h))   return false;
            if (!setMinutes(m)) return false;
            if (!setSeconds(s)) return false;
            return true;
        }

        int getHours()   const { 
            return hours;
        }
        int getMinutes() const {
            return minutes;
        }
        int getSeconds() const {
            return seconds;
        }

        int toSeconds() const
        {
            return hours * 3600 + minutes * 60 + seconds;
        }

        void addSeconds(int delta)
        {
            const int SECONDS_IN_DAY = 86400;
            int total = (toSeconds() + delta) % SECONDS_IN_DAY;
            if (total < 0)
            {
                total += SECONDS_IN_DAY;
            }

            hours = total / 3600;
            minutes = (total % 3600) / 60;
            seconds = total % 60;
        }

        bool isBefore(const Time& other) const 
        {
            return toSeconds() < other.toSeconds();
        }

        bool isAfter(const Time& other) const
        {
            return toSeconds() > other.toSeconds();
        }

        bool read(std::istream& in) {
            char c1, c2;
            int h, m, s;
            if (!(in >> h >> c1 >> m >> c2 >> s))
            {
                return false;
            }
            if (c1 != ':' || c2 != ':')
            {
                return false;
            }
            return setAll(h, m, s);
        }

        void write(std::ostream& out) const 
        {
            std::print(out, "{:02d}:{:02d}:{:02d}", hours, minutes, seconds);
        }
    };

    void insertionSort(Time* arr, int n) {
        for (int i = 1; i < n; i++) 
        {
            Time key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j].isAfter(key)) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

int main() {

    const int MAX = 64;
    Time times[MAX];
    int count = 0;

    std::ifstream in("times.txt");
    if (!in.is_open())
    {
        std::println( "Could not open times.txt");
        return -1;
    }

    while (count < MAX && times[count].read(in)) 
    {
        count++;
    }
    in.close();

    insertionSort(times, count);

    std::ofstream out("times_sorted.txt");

    for (int i = 0; i < count; i++) {
        times[i].write(std::cout);
        cout << '\n';

        if (out.is_open()) {
            times[i].write(out);
            out << '\n';
        }
    }
}



