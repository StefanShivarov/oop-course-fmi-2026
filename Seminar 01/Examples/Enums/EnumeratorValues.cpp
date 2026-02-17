#include <iostream>

enum Example {
    a, // 0
    b, // 1
    c = 5, // 5
    d, // 6
    e = 4, // 4
    f, // 5
    g = a + b, // 1
};

// we can specify the underlying type of the enumerator values!
enum BiggerEnum : uint64_t {
    first,
    second = INT_MAX, // 2147483647
    third // 2147483648
};

enum class UndefinedBehaviourExample {
    first,
    second = INT_MAX, // 2147483647
    third // compile-time error
};

enum class BiggerEnumClass : uint64_t {
    first,
    second = INT_MAX, // 2147483647
    third // 2147483648
};
