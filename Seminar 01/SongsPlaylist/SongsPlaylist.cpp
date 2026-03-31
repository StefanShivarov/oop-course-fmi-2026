#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::swap;

namespace Songs {

    namespace Constants {
        const int MAX_LENGTH = 51;
        const int DURATION_STR_LENGTH = 5;
        const char DELIMITER = '|';
    }

    struct Duration {
        int minutes;
        int seconds;
        int totalSeconds;
    };

    enum class Category {
        POP, ROCK, HIPHOP, JAZZ, LATIN, CHALGA, TECHNO, OTHER
    };

    using namespace Constants;

    struct Song {
        char name[MAX_LENGTH];
        char author[MAX_LENGTH];
        Duration duration;
        Category category;
    };


    namespace Utils {
        bool isDigit(char c) {
            return c >= '0' && c <= '9';
        }

        Duration parseDurationFromString(const char* str) {
            if (str == nullptr || strlen(str) != DURATION_STR_LENGTH) {
                return {};
            }

            for (int i = 0; i < DURATION_STR_LENGTH; i++) {
                if (i == 2) {
                    if (str[i] != ':') {
                        return {};
                    }
                    continue;
                }
                if (!isDigit(str[i])) {
                    return {};
                }
            }

            int minutes = (str[0] - '0') * 10 + (str[1] - '0');
            int seconds = (str[3] - '0') * 10 + (str[4] - '0');
            int totalSeconds = minutes * 60 + seconds;
            return { minutes, seconds, totalSeconds };
        }

        Category parseCategoryFromString(const char* str) {
            using enum Category;
            if (strcmp(str, "Pop") == 0) {
                return POP;
            }
            if (strcmp(str, "Rock") == 0) {
                return ROCK;
            }
            if (strcmp(str, "HipHop") == 0) {
                return HIPHOP;
            }
            if (strcmp(str, "Jazz") == 0) {
                return JAZZ;
            }
            if (strcmp(str, "Chalga") == 0) {
                return CHALGA;
            }
            if (strcmp(str, "Techno") == 0) {
                return TECHNO;
            }
            if (strcmp(str, "Latin") == 0) {
                return LATIN;
            }
            return OTHER;
        }

        const char* getCategoryName(Category category) {
            using enum Category;
            switch (category) {
                case POP: return "Pop";
                case ROCK: return "Rock";
                case HIPHOP: return "HipHop";
                case JAZZ: return "Jazz";
                case LATIN: return "Latin";
                case CHALGA: return "Chalga";
                case TECHNO: return "Techno";
                default: return "Other";
            }
        }

        bool compareByDuration(const Song& lhs, const Song& rhs) {
            return lhs.duration.totalSeconds < rhs.duration.totalSeconds;
        }

    }

    void readSong(Song& song, std::istream& is) {
        is.getline(song.name, 50, DELIMITER);
        is.getline(song.author, 50, DELIMITER);
        char buff[DURATION_STR_LENGTH + 1];
        is.getline(buff, DURATION_STR_LENGTH + 1, DELIMITER);
        song.duration = Utils::parseDurationFromString(buff);
        is.getline(buff, 10);
        song.category = Utils::parseCategoryFromString(buff);
    }

    void writeSong(const Song& song, std::ostream& os) {
        os << song.name << " | " << song.author << " | ";
        if (song.duration.minutes < 10) {
            os << '0';
        }
        os << song.duration.minutes << ':';
        if (song.duration.seconds < 10) {
            os << '0';
        }
        os << song.duration.seconds << " | " << Utils::getCategoryName(song.category) << '\n';
    }

    void sortSongs(Song* songs, size_t songsCount, bool (*comparator) (const Song&, const Song&)) {
        for (int i = 0; i < songsCount; i++) {
            int minIndex = i;
            for (int j = i + 1; j < songsCount; j++) {
                if (comparator(songs[j], songs[minIndex])) {
                    minIndex = j;
                }
            }

            if (i != minIndex) {
                swap(songs[i], songs[minIndex]);
            }
        }
    }

    void filterSongsByCriteria(const Song* songs, size_t songsCount, bool (*shouldFilter) (const Song&)) {
        for (int i = 0; i < songsCount; i++) {
            if (shouldFilter(songs[i])) {
                writeSong(songs[i], std::cout);
            }
        }
    }

    void getTopSongsByDuration(Song* songs, size_t songsCount, size_t limit) {
        if (limit > songsCount) {
            limit = songsCount;
        }

        sortSongs(songs, songsCount, [](const Song& s1, const Song& s2) { return s1.duration.totalSeconds > s2.duration.totalSeconds; });
        for (int i = 0; i < limit; i++) {
            writeSong(songs[i], std::cout);
        }
    }

    void getTotalDuration(const Song* songs, size_t songsCount) {
        int totalSecondsSum = 0;
        for (int i = 0; i < songsCount; i++) {
            totalSecondsSum += songs[i].duration.totalSeconds;
        }

        int hours = totalSecondsSum / 3600;
        int minutes = totalSecondsSum % 3600 / 60;
        int seconds = totalSecondsSum % 60;

        if (hours < 10) {
            cout << '0';
        }
        cout << hours << ":";

        if (minutes < 10) {
            cout << '0';
        }
        cout << minutes << ':';
        if (seconds < 10) {
            cout << '0';
        }
        cout << seconds << '\n';
    }

    void writeAllSongs(const Song* songs, size_t songsCount, std::ostream& os) {
        for (int i = 0; i < songsCount; i++) {
            writeSong(songs[i], os);
        }
    }

}

int main() {
    using namespace Songs;
    int n;
    cin >> n;
    cin.ignore(); // ignore the newline after the number of songs, so that getline works correctly in readSong

    Song* playlist = new Song[n];
    for (int i = 0; i < n; i++) {
        readSong(playlist[i], std::cin);
    }

    // sort songs by criteria
    cout << "Sort by duration:" << '\n';
    sortSongs(playlist, n, Utils::compareByDuration);
    writeAllSongs(playlist, n, cout);
    cout << '\n';

    // Filter songs with duration more than 200 seconds
    cout << "Filter by duration:" << '\n';
    filterSongsByCriteria(playlist, n, [](const Song& song) { return song.duration.totalSeconds > 200; });
    cout << '\n';

    // print total duration of playlist in format HH:MM:SS
    cout << "Total duration:" << '\n';
    getTotalDuration(playlist, n);
    cout << '\n';

    // top 3 songs by duration
    cout << "Top songs by duration:" << '\n';
    getTopSongsByDuration(playlist, n, 3);
    cout << '\n';

    // filter by category
    cout << "Filter songs by category:" << '\n';
    filterSongsByCriteria(playlist, n, [](const Song& song) { return song.category == Category::HIPHOP; });

    delete[] playlist; // !
}
