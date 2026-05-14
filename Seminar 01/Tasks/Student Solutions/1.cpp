#include <iostream>
const int MAX = 200;
const int MAX_ENTRIES = 20;
const int numberOfTypes = 4;
const int numberOfCharactersTime = 9;
enum class TYPE
{
    Info,
    Warn,
    Error,
    Debug
};

char type(TYPE t)
{
    if (t == TYPE::Info)
    {
        return 'I';
    }
    if (t == TYPE::Warn)
    {
        return 'W';
    }
    if (t == TYPE::Error)
    {
        return 'E';
    }
    if (t == TYPE::Debug)
    {
        return 'D';
    }
    else
        return '0';
}

struct Entry
{
    int hour;
    int minutes;
    int seconds;
    TYPE type;
    char Message[MAX];
};

void swap(Entry &a, Entry &b)
{
    Entry temp = a;
    a = b;
    b = temp;
}

void printEntry(Entry e)
{
    std::cout << "\n";
    if (e.hour <= 9)
    {
        std::cout << "0";
    }
    std::cout << e.hour;
    std::cout << ":";
    if (e.minutes <= 9)
    {
        std::cout << "0";
    }
    std::cout << e.minutes;

    std::cout << ":";
    if (e.seconds <= 9)
        std::cout << "0";
    std::cout << e.seconds;
    std::cout << " " << type(e.type) << " " << e.Message;
    std::cout << "\n";
}

int fromCharToInt(char s)
{
    if (s >= '0' && s <= '9')
        return s - '0';
    else
        return -1;
}

bool isValid(const char arr[])
{
    if (arr[0] > '2' || arr[0] < '0')
        return false;
    if (arr[1] > '9' || arr[1] < '0')
        return false;
    if (arr[1] > '3' && arr[0] == '2')
        return false;

    if (arr[2] != ':' || arr[5] != ':')
        return false;

    if (arr[3] > '5' || arr[3] < '0')
        return false;
    if (arr[4] > '9' || arr[4] < '0')
        return false;
    if (arr[6] > '5' || arr[6] < '0')
        return false;
    if (arr[7] > '9' || arr[7] < '0')
        return false;
    if (arr[8] != ' ' || arr[10] != ' ')
        return false;
    if (arr[9] != 'I' && arr[9] != 'W' && arr[9] != 'E' && arr[9] != 'D')
        return false;
    return true;
}

Entry convert(char *p)
{
    Entry result = {};
    result.hour = fromCharToInt(p[0]) * 10 + fromCharToInt(p[1]);
    result.minutes = fromCharToInt(p[3]) * 10 + fromCharToInt(p[4]);
    result.seconds = fromCharToInt(p[6]) * 10 + fromCharToInt(p[7]);
    if (p[9] == 'E')
        result.type = TYPE::Error;
    else if (p[9] == 'W')
        result.type = TYPE::Warn;
    else if (p[9] == 'D')
        result.type = TYPE::Debug;
    else if (p[9] == 'I')
        result.type = TYPE::Info;
    int i = 11;
    while (p[i] != '\0')
    {
        result.Message[i - 11] = p[i];
        i++;
    }
    return result;
}

void sortByTime(Entry arr[MAX_ENTRIES], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].hour > arr[j + 1].hour ||
                (arr[j].hour == arr[j + 1].hour && arr[j].minutes > arr[j + 1].minutes) || (arr[j].hour == arr[j + 1].hour && arr[j].minutes == arr[j + 1].minutes && arr[j].seconds > arr[j + 1].seconds))
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
void printAllEntriesSortedByTime(Entry arr[MAX_ENTRIES], int n)
{
    sortByTime(arr, n);
    for (int i = 0; i < n; i++)
    {
        std::cout << "\n";
        printEntry(arr[i]);
        std::cout << "\n";
    }
}

void printAllWithinTimeFrame(Entry arr[MAX_ENTRIES], int n, int start, int end)
{
    for (int i = 0; i < n; i++)
    {
        int seconds = arr[i].hour * 3600 + arr[i].minutes * 60 + arr[i].seconds;
        if (seconds >= start && seconds <= end)
        {
            printEntry(arr[i]);
        }
    }
}

void printAllEntriesFromType(Entry arr[MAX_ENTRIES], int n, int tip)
{
    for (int i = 0; i < n; i++)
    {
        if (static_cast<int>(arr[i].type) == (tip - 1))
            printEntry(arr[i]);
    }
}

int main()
{
    int n;
    int index = 0;
    Entry entries[MAX_ENTRIES];
    do
    {
        std::cin >> n;
        std::cin.ignore();
    } while (n < 0 || n > 100);
    char str[MAX][MAX];
    for (int i = 0; i < n; i++)
    {
        std::cin.getline(str[i], MAX);
        if (isValid(str[i]))
        {
            entries[index] = convert(str[i]);
            index++;
        }
        else
        {
            std::cout << "\nInvalid.\n";
        }
    }
    printAllEntriesSortedByTime(entries, n);
    int counters[numberOfTypes] = {0};
    for (int i = 0; i < n; i++)
    {
        counters[static_cast<int>(entries[i].type)]++;
    }
    for (int i = 0; i < numberOfTypes; i++)
    {
        std::cout << "\n"
                  << counters[i];
    }
    std::cout << "\nEarliest: ";
    printEntry(entries[0]);
    std::cout << "\nLatest: ";
    printEntry(entries[n - 1]);
    char start[numberOfCharactersTime];
    char end[numberOfCharactersTime];
    std::cout << "\nEnter start and end time respectively: ";
    std::cin >> start;
    std::cin >> end;
    // ostaveno e kato uprajnenie za chitatelq praveneto na proverka za validnostta na start/end.
    int secondsStart = (fromCharToInt(start[0]) * 10 + fromCharToInt(start[1])) * 3600 + 60 * (fromCharToInt(start[3]) * 10 + fromCharToInt(start[4])) + fromCharToInt(start[6]) * 10 + fromCharToInt(start[7]);
    int secondsEnd = (fromCharToInt(end[0]) * 10 + fromCharToInt(end[1])) * 3600 + 60 * (fromCharToInt(end[3]) * 10 + fromCharToInt(end[4])) + fromCharToInt(end[6]) * 10 + fromCharToInt(end[7]);
    printAllWithinTimeFrame(entries, n, secondsStart, secondsEnd);
    int tip;
    std::cout << "\nEnter 1-> Info, 2-> Warn, 3-> Error, 4-> Debug\n";
    std::cin >> tip;
    printAllEntriesFromType(entries, n, tip);
}