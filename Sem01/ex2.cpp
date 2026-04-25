#include <iostream>
#include <cstring>

using std::cin;
using std::cout;

enum Status {
    Waiting, InProgress, Done
};

struct Request {
    char registerNumber[100];
    char type;
    int emergency;
    Status status;

    void readRequest() {
        cin.getline(registerNumber, 100);
        cin >> type;
        cin >> emergency;

        cin.ignore();

        status = Waiting;
    }
};

void printRequest(Request request) {
    cout << request.registerNumber << " " << request.type << " " << request.emergency;
    cout << '\n';
}

void filterByStatus(Request* request, int N, Status target) {
    cout << "(filter by status): " << '\n';
    for (int i = 0; i < N; i++)
    {
        if (request[i].status == target) {
            printRequest(request[i]);
        }
    }
}

void startWork(Request* request, int N, char targetNumber[100]) {
    for (int i = 0; i < N; i++)
    {
        if ((strcmp(request[i].registerNumber, targetNumber) == 0)) {
            request[i].status = InProgress;
        }
    }
}

void finishWork(Request* request, int N, char targetNumber[100]) {
    for (int i = 0; i < N; i++)
    {
        if ((strcmp(request[i].registerNumber, targetNumber) == 0)) {
            request[i].status = Done;
        }
    }
}

void filterByType(Request* request, int N, char target) {
    cout << "filter by type of problem: ";
    for (int i = 0; i < N; i++)
    {
        if (request[i].type == target) {
            printRequest(request[i]);
        }
    }
}

void swap(Request& a, Request& b) {
    Request temp = a;
    a = b;
    b = temp;
}

void sortRequestByEmergency(Request* request, int N) {

    for (int i = 0; i < N -1; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if (request[j].emergency < request[j + 1].emergency) {
                swap(request[j], request[j + 1]);
            }           
        }
    }
}

void sortRequestByUrgency(Request* requests, int N) {
    sortRequestByEmergency(requests, N);

    cout << "Waiting- " << '\n';
    for (int i = 0; i < N; i++) {
        if (requests[i].status == Waiting) {
            printRequest(requests[i]);
        }
    }
}


int main()
{
    int N;
    cin >> N;
    cin.ignore();

    Request* myRequests = new Request[N];
    for (int i = 0; i < N; i++)
    {
        myRequests[i].readRequest();
    }

    cout << "\n";
    sortRequestByUrgency(myRequests, N);

    startWork(myRequests, N, myRequests[0].registerNumber);
    cout << "\n";

    cout << "In progress ";
    filterByStatus(myRequests, N, InProgress);
    cout << "\n";

    cout << "Waiting ";
    filterByStatus(myRequests, N, Waiting);
    cout << "\n";

    filterByType(myRequests, N, 'E');
    cout << "\n";

    delete[]myRequests;
}
