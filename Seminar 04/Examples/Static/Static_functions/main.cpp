#include <iostream>
int sum(int a, int b);

int main() {
    std::cout << sum(1, 2) << std::endl;
        // this will no longer be a conflict here
        // because it will choose the non-static function
        // since the static one is visible only within its own "translation unit" (b.cpp)
}