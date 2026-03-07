#include <iostream>
#include <sstream>

using std::stringstream;
using std::cout;

void printState(const std::istream& stream, const char* message) {
    cout << "---- " << message << " ----\n";
    cout << "good(): " << stream.good() << '\n';
    cout << "eof():  " << stream.eof() << '\n';
    cout << "fail(): " << stream.fail() << '\n';
    cout << "bad():  " << stream.bad() << '\n';
    cout << '\n';
}

int main() {
    
    {
        cout << "CASE 1: normal successful read\n\n";

        stringstream ss("123 456");

        printState(ss, "initial state");
        // all flags are false, so good() is true

        int x = 0;
        ss >> x; // successful read

        cout << "x = " << x << '\n';
        printState(ss, "after reading first integer successfully");
        // still no error flags
    }

    {
        cout << "CASE 2: failbit because of wrong format\n\n";

        stringstream ss("123 abc 456");

        int x = 0;
        ss >> x; // reads 123 successfully

        cout << "x = " << x << '\n';
        printState(ss, "after first successful read");

        ss >> x; // tries to read int from "abc" -> failbit is raised

        cout << "x = " << x << '\n';
        printState(ss, "after trying to read int from \"abc\"");
        // fail() becomes true
        // bad() is still false
        // eof() is usually false here
        // good() becomes false

        ss >> x; // this will do nothing, because the stream is still in fail state

        cout << "x = " << x << '\n';
        printState(ss, "after trying to read again while failbit is still raised");
        // once failbit is raised, later input operations usually do nothing
        // until we call clear()

        ss.clear(); // removes failbit
        printState(ss, "after clear()");
        // the stream is usable again, but it still points to "abc"

        ss.ignore(4); // skip 'a', 'b', 'c', ' '
        printState(ss, "after ignore(4)");
        // now the bad token is skipped

        ss >> x; // now it can read 456
        cout << "x = " << x << '\n';
        printState(ss, "after reading the next valid integer");
    }

    {
        cout << "CASE 3: eofbit and failbit at end of input\n\n";

        stringstream ss("42");

        int a = 0;
        int b = 0;

        ss >> a; // successful
        cout << "a = " << a << '\n';
        printState(ss, "after reading the only integer");
        // depending on the exact situation, eof might still be false here
        // because we have not yet tried to read past the end

        ss >> b; // tries to read past the available input
        cout << "b = " << b << '\n';
        printState(ss, "after trying to read past the end");
        // eofbit is raised because we reached the end
        // failbit is also raised because the read operation failed
        // badbit is still false

        ss.clear(); // remove eofbit/failbit
        printState(ss, "after clear()");
        // stream is logically usable again
        // but there is still no more data inside the stringstream
    }

    {
        cout << "CASE 4: reading a line after EOF\n\n";

        stringstream ss("hello");

        char buffer[32];
        ss.getline(buffer, 32); // reads "hello"
        cout << "buffer = " << buffer << '\n';
        printState(ss, "after first getline");
        // first getline succeeds

        ss.getline(buffer, 32); // there is no second line
        printState(ss, "after second getline");
        // this usually raises eofbit + failbit
        // because getline cannot extract another line
    }

    {
        cout << "CASE 5: manually raising badbit\n\n";

        stringstream ss("100");

        printState(ss, "initial state");

        ss.setstate(std::ios::badbit); // simulate serious stream corruption
        printState(ss, "after setstate(std::ios::badbit)");
        // bad() is true
        // fail() is also true, because fail() checks failbit OR badbit
        // good() is false

        int x = 0;
        ss >> x; // this will not work meaningfully while badbit is set
        cout << "x = " << x << '\n';
        printState(ss, "after trying to read while badbit is raised");

        ss.clear(); // technically removes badbit as well
        printState(ss, "after clear()");
        // for a real badbit situation, clear() may not truly solve the underlying problem
        // here it works only because we simulated badbit manually
    }

    {
        cout << "CASE 6: manually raising failbit\n\n";
        stringstream ss("999");

        printState(ss, "initial state");

        ss.setstate(std::ios::failbit);
        printState(ss, "after setstate(std::ios::failbit)");
        // fail() is true
        // bad() is false

        int x = 0;
        ss >> x; // blocked by failbit
        cout << "x = " << x << '\n';
        printState(ss, "after trying to read while failbit is raised");

        ss.clear();
        printState(ss, "after clear()");

        ss >> x; // now it works again
        cout << "x = " << x << '\n';
        printState(ss, "after successful read again");
    }

    {
        cout << "CASE 7: what fail() really means\n\n";

        stringstream ss1("abc");
        int x = 0;
        ss1 >> x; // raises failbit
        printState(ss1, "stream with failbit");
        // fail() is true because failbit is raised

        stringstream ss2("123");
        ss2.setstate(std::ios::badbit);
        printState(ss2, "stream with badbit");
        // fail() is also true here
        // because fail() checks whether failbit OR badbit is raised
    }

}
