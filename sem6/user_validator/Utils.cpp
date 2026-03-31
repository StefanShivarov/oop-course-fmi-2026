#include "Utils.h"
#include <iostream>
#pragma warning(disable:4996)


char* Utils::copyDynamicString(const char* src)
{
    if (src == nullptr) {
        char* result = new char[1];
        result[0] = '\0';
        return result;
    }

    char* result = new char[strlen(src) + 1];
    strcpy(result, src);

    return result;
}
