
#include <iostream>

using std::cin;
using std::cout;

namespace CarList {
    const int CAR_REGISTRATION_NUMBER = 9;

    enum Problem {
        E,
        B,
        T,
        G,
        S,
        O
    };

    enum Status {
        Waiting,
        InProgress,
        Done
    };

    struct Request {
        char carNumber[CAR_REGISTRATION_NUMBER];
        Problem problem;
        unsigned urgency;
        Status status;
    };

    const char* problemToArr(Problem p) {
        switch (p) {
        case E: return "Engine "; break;
        case B: return "Brakes "; break;
        case T: return "Tires "; break;
        case G: return "Gearbox "; break;
        case S: return "Suspension "; break;
        case O: return "Other "; break;
        }
    }

    const char* statusToArr(Status t){
        switch (t) {
        case Waiting:
            return "Waiting";
        case InProgress:
            return "InProgress";
        case Done:
            return "Done";
        }
    }

    bool areEqual(const char* a, const char* b) {
        int i = 0;

        while (a[i] != '\0' && b[i] != '\0') {
            if (a[i] != b[i])
                return false;
            i++;
        }

        return a[i] == '\0' && b[i] == '\0';
    }

    Problem charToProblem(const char letter) {
        switch (letter) {
        case 'E': return E; break;
        case 'B': return B; break;
        case 'T': return T; break;
        case 'G': return G; break;
        case 'S': return S; break;
        case 'O': return O; break;
        }
    }

    Status arrToStatus(const char* arr) {
        if (areEqual(arr, "Waiting"))
            return Waiting;
        if (areEqual(arr, "InProgress"))
            return InProgress;
        if (areEqual(arr, "Done"))
            return Done;
    }

    void printRequest(const Request& request) {
        cout << "Reg number is: " << request.carNumber << '\n';
        cout << problemToArr(request.problem) << '\n';
        cout << "Ergency: " << request.urgency << '\n';
        cout << statusToArr(request.status) << '\n';

    }

    void filterByStatus(Request requests[], int n, Status s) {
        for (int i = 0; i < n; i++) {
            if (requests[i].status == s) {
                printRequest(requests[i]);
            }
        }
    }

    bool startWork(Request request[], int n, const char carNum[]) {
        for (int i = 0; i < n; i++) {
            if (areEqual(request[i].carNumber, carNum)) {
                if (request[i].status == Waiting) {
                    request[i].status = InProgress;
                    return 1;
                }
                else {
                    cout << "Request has already been started.";
                    return 0;
                }
            }
        }
        cout << "No such request.";
        return 0;
    }

    bool FinishWork(Request request[], int n, const char carNum[]) {
        for (int i = 0; i < n; i++) {
            if (areEqual(request[i].carNumber, carNum)) {
                if (request[i].status == InProgress) {
                    request[i].status = Done;
                    return 1;
                }
                else {
                    cout << "Request is not in progress.";
                    return 0;
                }
            }
        }
        cout << "No such request.";
        return 0;   
    }

    bool isMoreUrgent(const Request& request1, const Request& request2) {
        return request1.urgency > request2.urgency;
    }

    void sortRequestsUrgency(Request request[], int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 1 - i; j++) {
                if (isMoreUrgent(request[j+1], request[j])) {
                    Request temp = request[j + 1];
                    request[j + 1] = request[j];
                    request[j] = temp;
                }
            }
        }
    }

    void filterByProblem(Request request[], int n, Problem p) {
        for (int i = 0; i < n; i++) {
            if (request[i].problem == p) {
                printRequest(request[i]);
            }
        }
    }

    int getLen(const char* str) {
        int counter = 0;
        while (str[counter] != 0)
            counter++;
        return counter;
    }

    bool isCarNumberValid(const Request& request) {
        return getLen(request.carNumber) > 0 && getLen(request.carNumber) < CAR_REGISTRATION_NUMBER;
    }

    bool isCharValid(const char c) {
        return c == 'E' || c == 'B' || c == 'T' || c == 'G' || c == 'S' || c == 'O';
    }

    bool isUrgencyValid(const unsigned t) {
        return t >= 1 && t <= 5;
    }
}

int main()
{
    using namespace CarList;

    int n;
    cout << "Enter number of requests: ";
    cin >> n;

    if (n <= 0)
        return 0;

    Request* requests = new Request[n];

    for (int i = 0; i < n; i++) {
        cout << "Registration number: ";
        cin >> requests[i].carNumber;   
        if (!isCarNumberValid(requests[i])) {
            delete[] requests;
            return -1;
        }
        char problemChar;
        cout << "Problem (E/B/T/G/S/O): ";
        cin >> problemChar;
        if (!isCharValid(problemChar)) {
            delete[] requests;
            return -1;
        }
        requests[i].problem = charToProblem(problemChar);
        cout << "Urgency (1-5): ";
        cin >> requests[i].urgency;
        if (!isUrgencyValid(requests[i].urgency)) {
            delete[] requests;
            return -1;
        }
        requests[i].status = Waiting;
    }

    cout << "\n--- Waiting requests ---\n";
    filterByStatus(requests, n, Waiting);

    cout << "\n--- Start work on car ABC123 ---\n";
    if (startWork(requests, n, "ABC123")) {
        cout << "Work started successfully.\n";
    }

    cout << "\n--- Updated status for ABC123 ---\n";
    filterByStatus(requests, n, InProgress);

    cout << "\n--- Finish work on car ABC123 ---\n";
    if (FinishWork(requests, n, "ABC123")) {
        cout << "Work finished successfully.\n";
    }

    cout << "\n--- Filter requests with Engine problem ---\n";
    filterByProblem(requests, n, E);

    cout << "\n--- Requests sorted by urgency ---\n";
    sortRequestsUrgency(requests, n);
    for (int i = 0; i < n; i++) {
        printRequest(requests[i]);
    }


    delete[] requests;

    return 0;
}