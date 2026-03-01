#include <print>
#include <format>
#include <fstream>

int main() {
    int a = 15;
    int b = 27;
    int x = 255;
    int fn = 12345;
    double pi = 3.14159265359;
    double price = 12.3456;
    int quantity = 3;
    const char* name = "John Doe";

    // 1) Basic formatting
    std::println("Basic formatting:");
    std::println("{} + {} = {}", a, b, a + b);
    std::println("Hello, {}!", name);
    std::println();

    // 2) Argument indexing
    std::println("Argument indexing:");
    std::println("{0} scored {1} points", name, 95);
    std::println("{1} comes after {0}", "first", "second");
    std::println("{0} {0} {1}", "ha", "!");
    std::println();

    // 3) Floating point formatting / rounding for output
    std::println("Floating point formatting:");
    std::println("Default: {}", pi);
    std::println("2 digits after decimal: {:.2f}", pi);
    std::println("4 digits after decimal: {:.4f}", pi);
    std::println("Scientific notation: {:.3e}", pi);
    std::println("General format: {:.5g}", pi);
    std::println();

    // 4) Width and alignment
    std::println("Width and alignment:");
    std::println("|{:>10}|", 42);   // right aligned
    std::println("|{:<10}|", 42);   // left aligned
    std::println("|{:^10}|", 42);   // centered
    std::println();

    // 5) Fill characters
    std::println("Fill characters:");
    std::println("|{:*^10}|", 42);
    std::println("|{:0>8}|", 123);
    std::println("|{:_<8}|", 123);
    std::println();

    // 6) Integer formatting in different number systems
    std::println("Integer formatting:");
    std::println("decimal: {}", x);
    std::println("hex: {:x}", x);
    std::println("HEX: {:X}", x);
    std::println("binary: {:b}", x);
    std::println("octal: {:o}", x);
    std::println("hex with prefix: {:#x}", x);
    std::println("binary with prefix: {:#b}", x);
    std::println();

    // 7) Combining indexing and formatting
    std::println("Combining indexing and formatting:");
    std::println("price = {0:.2f}, quantity = {1}, total = {2:.2f}",
                 price, quantity, price * quantity);
    std::println("Reordered: grade={1:.1f}, name={0}", name, 5.6789);
    std::println();

    // 8) Useful zero-padding example
    std::println("Zero-padding:");
    std::println("FN: {:06}", fn);
    std::println("Date-like formatting: {:04d}-{:02d}-{:02d}", 2026, 2, 24);
    std::println("{}", std::format("File name: {:04d}-{:02d}-{:02d}", 2026, 2, 24));
    std::println();

    // 9) Table-like output
    std::println("Table-like output:");
    std::println("|{:^12}|{:^8}|{:^10}|", "Name", "Age", "Score");
    std::println("|{:-^12}|{:-^8}|{:-^10}|", "", "", "");
    std::println("|{:<12}|{:>8}|{:>10.2f}|", "Alice", 20, 5.75);
    std::println("|{:<12}|{:>8}|{:>10.2f}|", "Bob", 19, 4.50);
    std::println();

    // 10) Printing to a file stream
    std::ofstream out("format_demo.txt");
    if (out.is_open()) {
        std::println(out, "Name: {}", name);
        std::println(out, "FN: {:06}", fn);
        std::println(out, "Pi rounded: {:.2f}", pi);
        std::println(out, "Hex value: {:#x}", x);
        std::println(out, "Total: {:.2f}", price * quantity);
    }

}
