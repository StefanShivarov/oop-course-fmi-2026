#include <iostream>
#include <cstring>

using std::cin;
using std::cout;

namespace TimeUtils {

    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }
    // "HH:MM" -> minutes since 00:00, invalid -> -1
    int parseFromString(const char* str) {
        if (str == nullptr) {
            return -1;
        }

        if (strlen(str) != 5) {
            return -1;
        }

        if (str[2] != ':') {
            return -1;
        }

        if (!isDigit(str[0]) || !isDigit(str[1]) || !isDigit(str[3]) || !isDigit(str[4])) {
            return -1;
        }

        int hours = (str[0] - '0') * 10 + (str[1] - '0');
        int minutes = (str[3] - '0') * 10 + (str[4] - '0');

        if (hours < 0 || hours > 23) {
            return -1;
        }

        if (minutes < 0 || minutes > 59) {
            return -1;
        }

        return hours * 60 + minutes;
    }
}

namespace HexUtils {
    // "0x1A3F" or "0X1A3F" -> integer, invalid -> -1
    int parseFromString(const char* str) {
        if (!str) {
            return -1;
        }
        if (!(str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))) {
            return -1;
        }

        int value = 0;
        for (int i = 2; str[i] != '\0'; i++) {
            int digit;
            if (str[i] >= '0' && str[i] <= '9') {
                digit = str[i] - '0';
            }
            else if (str[i] >= 'a' && str[i] <= 'f') {
                digit = 10 + (str[i] - 'a');
            }
            else if (str[i] >= 'A' && str[i] <= 'F') {
                digit = 10 + (str[i] - 'A');
            }
            else {
                return -1;
            }

            value = value * 16 + digit;
        }

        return value;
    }
}

int main() {
    cout << TimeUtils::parseFromString("09:45") << "\n";
    cout << HexUtils::parseFromString("0x1A3F") << "\n";
}
