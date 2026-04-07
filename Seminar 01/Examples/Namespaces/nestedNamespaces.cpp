#include <iostream>

namespace app {
    int value = 10;

    namespace config {
        int value = 20;          // hides app::value inside app::config
        const int MaxUsers = 3;  // visible as app::config::MaxUsers
    }

    namespace math {
        int value = 30;          // hides app::value inside app::math

        int addToValue(int x) {
            // Here, unqualified "value" means app::math::value
            return value + x;
        }

        namespace detail {
            int value = 40;      // hides app::math::value inside app::math::detail

            int compute(int x) {
                // Unqualified lookup:
                // value -> app::math::detail::value
                // config is found in enclosing namespace app
                int a = value;                 // 40
                int b = app::math::value;      // 30 (explicitly choose the outer one)
                int c = app::value;            // 10
                int d = app::config::value;    // 20

                // MaxUsers is in app::config
                int limit = app::config::MaxUsers;

                return a + b + c + d + limit + x;
            }
        }
    }
}

int main() {
    cout << "app::value = " << app::value << "\n";
    cout << "app::config::value = " << app::config::value << "\n";
    cout << "app::math::value = " << app::math::value << "\n";
    cout << "app::math::detail::value = " << app::math::detail::value << "\n";

    cout << "app::math::addToValue(5) = " << app::math::addToValue(5) << "\n";
    cout << "app::math::detail::compute(1) = " << app::math::detail::compute(1) << "\n";

    // Bringing names into scope:
    using namespace app::config;
    // Now "MaxUsers" and "value" refer to app::config::...
    cout << "MaxUsers (via using) = " << MaxUsers << "\n";
    cout << "value (via using app::config) = " << value << "\n";

    // If you also do:
    // using namespace app::math;
    // then "value" becomes ambiguous (config::value vs math::value).
}
