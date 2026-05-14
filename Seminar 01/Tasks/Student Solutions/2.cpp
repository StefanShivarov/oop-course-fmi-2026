#include <iostream>
const int MAX_PLATE_NUMBERS = 9;
const int MAX_REQUESTS = 9;
enum class Issue
{
    Engine,
    Brakes,
    Tires,
    Gearbox,
    Suspension,
    Other
};
enum class Status
{
    Waiting,
    InProgress,
    Done
};
struct Request
{
    char license_plate[MAX_PLATE_NUMBERS];
    Issue issue;
    int urgency;
    Status status = Status::Waiting;
};

Request enterRequest()
{
    Request request;
    std::cout << "\nEnter license plate: ";
    std::cin >> request.license_plate;
    std::cout << "\nEnter issue: ";
    char issueCharacter;
    Issue issue;
    std::cin >> issueCharacter;
    switch (issueCharacter)
    {
    case 'E':
        issue = Issue::Engine;
        break;
    case 'B':
        issue = Issue::Brakes;
        break;
    case 'T':
        issue = Issue::Tires;
        break;
    case 'G':
        issue = Issue::Gearbox;
        break;
    case 'S':
        issue = Issue::Suspension;
        break;
    default:
        issue = Issue::Other;
        break;
    }
    request.issue = issue;
    std::cout << "\nEnter urgency: ";
    std::cin >> request.urgency;
    return request;
}

char getIssue(const Request& request)
{
    switch (request.issue)
    {
    case Issue::Engine:
        return 'E';
    case Issue::Brakes:
        return 'B';
    case Issue::Tires:
        return 'T';
    case Issue::Gearbox:
        return 'G';
    case Issue::Suspension:
        return 'S';
    default:
        return 'O';
    }
}
char getStatus(Request request)
{
    switch (request.status)
    {
    case Status::Waiting:
        return 'W';
    case Status::InProgress:
        return 'I';
    default:
        return 'D';
    }
}
void printRequest(const Request& request)
{
    std::cout << "\nLicense plate: " << request.license_plate;
    std::cout << "\n Issue: " << getIssue(request);
    std::cout << "\n Urgency: " << request.urgency;
    std::cout << "\n Status: " << getStatus(request);
}

void printRequestByIssue(const Request requests[MAX_REQUESTS], int n, Issue issue)
{
    for (int i = 0; i < n; i++)
    {
        if (requests[i].issue == issue)
            printRequest(requests[i]);
    }
}

void swap(Request &req1, Request &req2)
{
    Request temp = req1;
    req1 = req2;
    req2 = temp;
}

void printRequestByStatus(const Request requests[MAX_REQUESTS], int n, Status status)
{
    for (int i = 0; i < n; i++)
    {
        if (requests[i].status == status)
            printRequest(requests[i]);
    }
}

void sortByUrgency(Request requests[MAX_REQUESTS], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (requests[j].urgency < requests[j + 1].urgency)
                swap(requests[j], requests[j + 1]);
        }
    }
}

void printRequests(const Request requests[MAX_REQUESTS], int n)
{
    for (int i = 0; i < n; i++)
    {
        printRequest(requests[i]);
    }
}

int length(char l[MAX_PLATE_NUMBERS])
{
    int count = 0;
    while (l[count] != '\0')
        count++;
    return count;
}
bool compareLicenses(char license_plate1[MAX_PLATE_NUMBERS], char license_plate2[MAX_PLATE_NUMBERS])
{
    int len = length(license_plate1);
    for (int i = 0; i < len + 1; i++)
    {
        if (license_plate1[i] != license_plate2[i])
            return false;
    }
    return true;
}

void startWorkOnRequest(Request requests[MAX_REQUESTS], int n, char license_plate[MAX_PLATE_NUMBERS])
{
    for (int i = 0; i < n; i++)
    {
        if (compareLicenses(requests[i].license_plate, license_plate))
            requests[i].status = Status::InProgress;
    }
}

void endRequest(Request requests[MAX_REQUESTS], int n, char license_plate[MAX_PLATE_NUMBERS])
{
    for (int i = 0; i < n; i++)
    {
        if (compareLicenses(requests[i].license_plate, license_plate))
            requests[i].status = Status::Done;
    }
}

int main()
{
    int n;
    do
    {
        std::cin >> n;
    } while (n > MAX_REQUESTS);

    Request requests[MAX_REQUESTS];
    for (int i = 0; i < n; i++)
    {
        requests[i] = enterRequest();
    }
    Request r = requests[2];
    sortByUrgency(requests, n);
    startWorkOnRequest(requests,n,r.license_plate);
    printRequests(requests,n); 
}