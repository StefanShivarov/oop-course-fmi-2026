#include <iostream>
#include "MyString.h"

using std::cout;

int main()
{
    // 1. Construction
    MyString s1;
    MyString s2("Hello");
    MyString s3("World");

    cout << "s1 = \"" << s1 << "\"\n";
    cout << "s2 = \"" << s2 << "\"\n";
    cout << "s3 = \"" << s3 << "\"\n";

    // 2. Copy constructor
    MyString copy = s2;
    cout << "copy = \"" << copy << "\"\n";

    // 3. Copy assignment
    s1 = s3;
    cout << "s1 after copy assignment = \"" << s1 << "\"\n";

    // 4. operator+
    MyString combined = s2 + MyString(" ") + s3;
    cout << "combined = \"" << combined << "\"\n";

    // 5. operator+=
    combined += MyString("!");
    cout << "combined after += = \"" << combined << "\"\n";

    // 6. Indexing
    cout << "combined[1] = " << combined[1] << "\n";
    combined[0] = 'h';
    cout << "combined after modifying [0] = \"" << combined << "\"\n";

    // 7. length() and c_str()
    cout << "combined.length() = " << combined.length() << "\n";
    cout << "combined.c_str() = " << combined.c_str() << "\n";

    // 8. Comparisons
    MyString a("abc");
    MyString b("abc");
    MyString c("abd");

    cout << "a == b -> " << (a == b) << "\n";
    cout << "a != c -> " << (a != c) << "\n";
    cout << "a < c  -> " << (a < c) << "\n";
    cout << "c > b  -> " << (c > b) << "\n";
    cout << "a <= b -> " << (a <= b) << "\n";
    cout << "c >= a -> " << (c >= a) << "\n";

    // 9. Move constructor
    MyString temp("temporary object");
    MyString moved(std::move(temp));

    cout << "moved = \"" << moved << "\"\n";
    cout << "temp after move = \"" << temp << "\"\n";

    // 10. Move assignment
    MyString x("first");
    MyString y("second");

    x = std::move(y);

    cout << "x after move assignment = \"" << x << "\"\n";
    cout << "y after move assignment = \"" << y << "\"\n";

    // 11. Input from the console
    MyString input;
    cout << "Enter a word: ";
    std::cin >> input;
    cout << "You entered: \"" << input << "\"\n";

    return 0;
}
