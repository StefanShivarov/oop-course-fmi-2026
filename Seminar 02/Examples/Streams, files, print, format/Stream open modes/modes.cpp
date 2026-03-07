#include <iostream>
#include <sstream>
#include <fstream>

using std::stringstream;
using std::cout;
using std::ofstream;

void printFile(const char* fileName) {
    std::ifstream in(fileName);
    std::cout << "Contents of \"" << fileName << "\": ";
    char ch;
    while (in.get(ch)) {
        std::cout << ch;
    }
    std::cout << "\n\n";
    in.close();
}

int main() {
    const char* fileName = "modes_demo.txt";

    // ios::out
    // Opens the file for writing.
    // With ofstream, this usually removes the old file contents.
    {
        std::ofstream out(fileName, std::ios::out);
        out << "first line\n";
    }
    std::cout << "ios::out\n";
    printFile(fileName);

    // ios::app
    // Every write operation goes to the end of the file.
    // Even if we move the put pointer with seekp, writing still happens at the end.
    {
        std::ofstream out(fileName, std::ios::app);
        out << "second line\n";
    }
    std::cout << "ios::app\n";
    printFile(fileName);

    {
        std::ofstream out(fileName, std::ios::app);
        out.seekp(0); // attempt to move to the beginning
        out << "XXX\n"; // with app, this still gets written at the end
    }
    std::cout << "ios::app ignores seekp for writing\n";
    printFile(fileName);

    // ios::trunc
    // If the file already exists, its contents are erased when opening.
    {
        std::ofstream out(fileName, std::ios::out | std::ios::trunc);
        out << "file was truncated\n";
    }
    std::cout << "ios::trunc\n";
    printFile(fileName);

    // ios::ate
    // The stream starts at the end when opened,
    // BUT later we are allowed to move with seekp/seekg and write somewhere else.
    // This is the important difference from app.
    {
        std::ofstream out(fileName, std::ios::out | std::ios::ate);
        out.seekp(0); // with ate we can move back to the beginning
        out << "BEGIN\n";
    }
    std::cout << "ios::ate\n";
    printFile(fileName);

    // app vs ate side by side
    {
        std::ofstream out(fileName, std::ios::out | std::ios::trunc);
        out << "abcdef\n";
    }

    {
        std::ofstream out(fileName, std::ios::out | std::ios::app);
        out.seekp(0);
        out << "APP";
    }
    std::cout << "app: write still goes to the end\n";
    printFile(fileName);

    {
        std::ofstream out(fileName, std::ios::out | std::ios::trunc);
        out << "abcdef\n";
    }

    {
        std::ofstream out(fileName, std::ios::out | std::ios::ate);
        out.seekp(0);
        out << "ATE";
    }
    std::cout << "ate: seekp works, so writing can happen at the beginning\n";
    printFile(fileName);

    // Wrong combinations: stream type vs open mode
    {
        std::ifstream in("wrong_combo_1.txt", std::ios::out);
        std::cout << "ifstream with ios::out\n";
        std::cout << "  is_open(): " << in.is_open() << '\n';
        std::cout << "  fail():    " << in.fail() << "\n\n";
    }

    {
        std::ofstream out("wrong_combo_2.txt", std::ios::in);
        std::cout << "ofstream with ios::in\n";
        std::cout << "  is_open(): " << out.is_open() << '\n';
        std::cout << "  fail():    " << out.fail() << "\n\n";
    }


    // _Nocreate / _Noreplace
    // ios::_Nocreate  -> open only if the file already exists
    // ios::_Noreplace -> open only if the file does NOT exist


    // Summary:
    //   out   -> write
    //   in    -> read
    //   trunc -> erase old contents when opening
    //   app   -> every write goes to the end
    //   ate   -> start at the end, but later seekp/seekg can move the position
    //   binary-> binary mode, used together with in/out
    //
    // Important difference:
    //   app = always write at the end
    //   ate = start at the end, but later you may write elsewhere
}
