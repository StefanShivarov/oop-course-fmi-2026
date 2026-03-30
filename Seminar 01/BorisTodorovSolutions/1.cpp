#include <iostream>
#include <print>
#include <string>
using namespace std;
int convertTwoCharsToInteger(char c1, char c2)
{
    return (c1 - '0') * 10 + c2 - '0';
}
enum class logType
{
    Info,
    Warning,
    Error,
    Debug
};

class Log
{
private:
    int hours, minutes, seconds;
    logType type;
    string message;

    char logTypeToChar(logType t) const
    {
        switch (t)
        {
        case logType::Info:
            return 'I';
        case logType::Warning:
            return 'W';
        case logType::Error:
            return 'E';
        case logType::Debug:
            return 'D';
        default:
            return '?';
        }
    }
    logType charToLogType(char c) const
    {
        switch (c)
        {
        case 'I':
            return logType::Info;
        case 'W':
            return logType::Warning;
        case 'E':
            return logType::Error;
        case 'D':
            return logType::Debug;
        default:
            print("Error converting char to logType");
            return logType::Error;
        }
    }
public:
    logType giveType() const
    {
        return type;
    }
    char giveTypeAsChar() const
    {
        return logTypeToChar(type);
    }
    void printGivenLog() const
    {
        println("{:02}:{:02}:{:02} {} {}",hours,minutes,seconds,logTypeToChar(type), message);
    }
    int returnTotalTimeInSeconds() const
    {
        return hours * 3600 + minutes * 60 + seconds;
    }
    Log(string unformattedLog) 
    {
        hours = convertTwoCharsToInteger(unformattedLog[0], unformattedLog[1]);
        minutes = convertTwoCharsToInteger(unformattedLog[3], unformattedLog[4]);
        seconds = convertTwoCharsToInteger(unformattedLog[6], unformattedLog[7]);
        type = charToLogType(unformattedLog[9]);
        message = unformattedLog.substr(11);
    }
    Log() : hours(0), minutes(0), seconds(0), type(logType::Info), message("Empty log") {

    }
};
int charToInt(char c)
{
    return c - '0';
}
int stringToIntAndReturnTotalTime(string time)
{
    //format 00:00:00
    return(charToInt(time[0]) * 10 + charToInt(time[1])) * 3600 + (charToInt(time[3]) * 10 + charToInt(time[4])) * 60 + charToInt(time[6]) * 10 + charToInt(time[7]);
}
void swapLogs(Log& log1, Log& log2)
{
    Log temp = log1;
    log1 = log2;
    log2 = temp;
}
void printNLogsByTime (const int n,const Log* logs)
{
    Log* sortedLogs = new Log[n];
    for (int i=0;i < n;i++)
    {
        sortedLogs[i] = logs[i];
    }
    bool swapped;
    for (int i = 0;i < n - 1;i++)
    {
        swapped = false;
        for (int j = 0;j < n - i - 1;j++)
        {
            if (sortedLogs[j].returnTotalTimeInSeconds() > sortedLogs[j + 1].returnTotalTimeInSeconds())
            {
                swapLogs(sortedLogs[j], sortedLogs[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
    for (int i = 0;i < n;i++)
    {
        sortedLogs[i].printGivenLog();
    }
    delete[] sortedLogs;
}
void printAmountOfEveryType(const int n, const Log* logs)
{
    //0-info,1-warning,2-error,3-debug
    int countByTypes[4] = { 0 };
    for (int i = 0;i < n;i++)
    {
        switch (logs[i].giveType())
        {
        case logType::Info:
            countByTypes[0]++;
            break;
        case logType::Warning:
            countByTypes[1]++;
            break;
        case logType::Error:
            countByTypes[2]++;
            break;
        case logType::Debug:
            countByTypes[3]++;
            break;
        }
    }
    println("Info logs amount - {}", countByTypes[0]);
    println("Warning logs amount - {}", countByTypes[1]);
    println("Error logs amount - {}", countByTypes[2]);
    println("Debug logs amount - {}", countByTypes[3]);
}
void printEarliestAndLatestLogs(const int n, const Log* logs)
{
    int index = 0;
    int time = logs[0].returnTotalTimeInSeconds();
    for (int i = 0;i < n;i++)
    {
        if (logs[i].returnTotalTimeInSeconds() < time)
        {
            index = i;
            time = logs[i].returnTotalTimeInSeconds();
        }
    }
    logs[index].printGivenLog();
    for (int i = 0;i < n;i++)
    {
        if (logs[i].returnTotalTimeInSeconds() > time)
        {
            index = i;
            time = logs[i].returnTotalTimeInSeconds();
        }
    }
    logs[index].printGivenLog();
}
void formatLogsByType(const int n, const Log* logs)
{
    char t;
    cin >> t;
    for (int i = 0;i < n;i++)
    {
        if (logs[i].giveTypeAsChar() == t)
        {
            logs[i].printGivenLog();
        }
    }
}
void formatLogsByTimeInterval(const int n, const Log* logs)
{
    string startTime;
    string endTime;
    getline(cin, startTime);
    getline(cin, endTime);
    int startTimeInSec = stringToIntAndReturnTotalTime(startTime);
    int endTimeInSec = stringToIntAndReturnTotalTime(endTime);
    for (int i = 0;i < n;i++)
    {
        if (logs[i].returnTotalTimeInSeconds() >= startTimeInSec && logs[i].returnTotalTimeInSeconds() <= endTimeInSec)
        {
            logs[i].printGivenLog();
        }
    }
}
int main()
{
    int n = 0;
    cin >> n;
    cin.ignore();
    Log* logs = new Log[n];
    for (int i = 0;i < n;i++)
    {
        string unformattedLog;
        getline(cin,unformattedLog);
        logs[i] = Log(unformattedLog);
    }
    println("\nAmount of every type of log:");
    printAmountOfEveryType(n, logs);

    println("\nEarliest and latest logs:");
    printEarliestAndLatestLogs(n, logs);

    println("\nSorted by time:");
    printNLogsByTime(n, logs);

    println("\nFilter by type:");
    println("Enter a type (I, W, E, D):");
    formatLogsByType(n, logs);
    cin.ignore();

    println("\nFilter by time interval:");
    println("Enter start time and end time (HH:MM:SS):");
    formatLogsByTimeInterval(n, logs);

    delete[] logs;
}
