#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;

namespace Constants {
    const int MAX_PLATE_LENGTH = 9;
}

enum class ProblemType {
    ENGINE, BRAKES, TIRES, GEARBOX, SUSPENSION, OTHER
};

enum class RequestStatus {
    WAITING, IN_PROGRESS, DONE
};

struct RepairRequest {
    char plate[Constants::MAX_PLATE_LENGTH] = "";
    ProblemType type = ProblemType::OTHER;
    int urgency = 1; // 1..5
    RequestStatus status = RequestStatus::WAITING;
    int order = 0;
};

namespace utils {
    ProblemType parseProblemTypeFromChar(char c) {
        switch (c) {
            case 'E': return ProblemType::ENGINE;
            case 'B': return ProblemType::BRAKES;
            case 'T': return ProblemType::TIRES;
            case 'G': return ProblemType::GEARBOX;
            case 'S': return ProblemType::SUSPENSION;
            default: return ProblemType::OTHER;
        }
    }

    char convertProblemTypeToChar(ProblemType t) {
        switch (t) {
            case ProblemType::ENGINE: return 'E';
            case ProblemType::BRAKES: return 'B';
            case ProblemType::TIRES: return 'T';
            case ProblemType::GEARBOX: return 'G';
            case ProblemType::SUSPENSION: return 'S';
            default: return 'O';
        }
    }

    const char* convertProblemTypeToString(ProblemType t) {
        switch (t) {
            case ProblemType::ENGINE: return "Engine";
            case ProblemType::BRAKES: return "Brakes";
            case ProblemType::TIRES: return "Tires";
            case ProblemType::GEARBOX: return "Gearbox";
            case ProblemType::SUSPENSION: return "Suspension";
            default: return "Other";
        }
    }

    RequestStatus parseStatusFromString(const char* s) {
        if (strcmp(s, "Waiting") == 0) {
            return RequestStatus::WAITING;
        }
        if (strcmp(s, "InProgress") == 0) {
            return RequestStatus::IN_PROGRESS;
        }
        if (strcmp(s, "Done") == 0) {
            return RequestStatus::DONE;
        }
        return RequestStatus::WAITING;
    }

    const char* convertStatusToString(RequestStatus st) {
        switch (st) {
            case RequestStatus::WAITING: return "Waiting";
            case RequestStatus::IN_PROGRESS: return "InProgress";
            case RequestStatus::DONE: return "Done";
            default: return "Waiting";
        }
    }

    int findRequestIndexByPlate(const RepairRequest* reqs, size_t n, const char* plate) {
        for (size_t i = 0; i < n; i++) {
            if (strcmp(reqs[i].plate, plate) == 0) {
                return i;
            }
        }
        return -1;
    }
}

void readRequest(RepairRequest& r, int order, istream& is = cin) {
    // <plate> <typeLetter> <urgency> <status>
    // CA1234AB E 5 Waiting
    char typeLetter = 'O';
    char statusBuff[16];
    is >> r.plate >> typeLetter >> r.urgency >> statusBuff;

    r.type = utils::parseProblemTypeFromChar(typeLetter);

    if (r.urgency < 1) {
        r.urgency = 1;
    }
    if (r.urgency > 5) {
        r.urgency = 5;
    }

    r.status = utils::parseStatusFromString(statusBuff);
    r.order = order;
}

void writeRequest(const RepairRequest& r, ostream& os = cout) {
    os << r.plate << ' ';
    os << utils::convertProblemTypeToChar(r.type) << ' ';
    os << r.urgency << ' ';
    os << utils::convertStatusToString(r.status);
    os << '\n';
}

void sortRequests(RepairRequest* reqs, size_t n, bool (*comparator)(const RepairRequest&, const RepairRequest&)) {
    for (size_t i = 0; i < n; i++) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < n; j++) {
            if (comparator(reqs[j], reqs[minIndex])) {
                minIndex = j;
            }
        }
        if (i != minIndex) {
            std::swap(reqs[i], reqs[minIndex]);
        }
    }
}

void filterRequests(const RepairRequest* reqs, size_t n, bool (*shouldPrint)(const RepairRequest&),
                    ostream& os = cout) {
    for (size_t i = 0; i < n; i++) {
        if (shouldPrint(reqs[i])) {
            writeRequest(reqs[i], os);
        }
    }
}

void writeAllRequests(const RepairRequest* reqs, size_t n, ostream& os = cout) {
    filterRequests(reqs, n, [](const RepairRequest&) { return true; });
}

bool startWork(RepairRequest* reqs, size_t n, const char* plate) {
    int index = utils::findRequestIndexByPlate(reqs, n, plate);
    if (index == -1) {
        return false;
    }
    if (reqs[index].status != RequestStatus::WAITING) {
        return false;
    }
    reqs[index].status = RequestStatus::IN_PROGRESS;
    return true;
}

bool finishWork(RepairRequest* reqs, size_t n, const char* plate) {
    int index = utils::findRequestIndexByPlate(reqs, n, plate);
    if (index == -1) {
        return false;
    }
    if (reqs[index].status != RequestStatus::IN_PROGRESS) {
        return false;
    }
    reqs[index].status = RequestStatus::DONE;
    return true;
}

void printWaitingRequestsSortedByUrgencyThenByOrder(RepairRequest* reqs, size_t n) {
    sortRequests(reqs, n, [](const RepairRequest& a, const RepairRequest& b) {
        if (a.urgency != b.urgency) {
            return a.urgency > b.urgency;
        }
        return a.order < b.order;
    });

    filterRequests(reqs, n, [](const RepairRequest& r) { return r.status == RequestStatus::WAITING; });
}

int main() {
    int n;
    cin >> n;

    RepairRequest* reqs = new RepairRequest[n];
    for (int i = 0; i < n; i++) {
        readRequest(reqs[i], i);
    }

    cout << "All requests\n";
    writeAllRequests(reqs, n);

    cout << "Start work: CA1234AB\n";
    startWork(reqs, n, "CA1234AB");

    cout << "Finish work: CA1234AB\n";
    finishWork(reqs, n, "CA1234AB");

    cout << "Filter by status: Waiting\n";
    filterRequests(reqs, n, [](const RepairRequest& r) { return r.status == RequestStatus::WAITING; });

    cout << "Sort waiting requests by urgency (desc) then by order\n";
    printWaitingRequestsSortedByUrgencyThenByOrder(reqs, n);

    cout << "Filter by type: Brakes\n";
    filterRequests(reqs, n, [](const RepairRequest& r) { return r.type == ProblemType::BRAKES; });

    cout << "Filter by status: Done\n";
    filterRequests(reqs, n, [](const RepairRequest& r) { return r.status == RequestStatus::DONE; });

    delete[] reqs;
}
