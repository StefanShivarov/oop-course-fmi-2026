#include "Utils.h"
#include <cstring>

namespace utils {

    char* copyDynamicString(const char* src) {
        if (!src) {
            char* result = new char[1];
            result[0] = '\0';
            return result;
        }

        size_t len = strlen(src) + 1;
        char* result = new char[len];
        strcpy_s(result, len, src);
        return result;
    }

}

