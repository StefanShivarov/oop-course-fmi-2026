#include <iostream>
#include <cstring>

namespace Service {
    enum class ProblemType {
        Engine,
        Brakes,
        Tires,
        Gearbox,
        Suspension,
        Other
	};

    ProblemType parseCharToProblemType(char problemType) {
        switch (problemType) {
            case 'E': return ProblemType::Engine;
            case 'B': return ProblemType::Brakes;
            case 'T': return ProblemType::Tires;
            case 'G': return ProblemType::Gearbox;
            case 'S': return ProblemType::Suspension;
            case 'O': return ProblemType::Other;
        }
	}

    char parseProblemTypeToChar(ProblemType problemType) {
        switch (problemType) {
            case ProblemType::Engine: return 'E';
            case ProblemType::Brakes: return 'B';
            case ProblemType::Tires: return 'T';
            case ProblemType::Gearbox: return 'G';
            case ProblemType::Suspension: return 'S';
            case ProblemType::Other: return 'O';
        }
    }

    enum class RequestStatus {
        Waiting,
        InProgress,
        Done
    };

    enum class Priority {
        Low = 1,
        Normal,
        Medium,
        High,
        Emergency
    };

    struct Request {
		char plateNumber[10];
        ProblemType problem;
		RequestStatus status = RequestStatus::Waiting;
        Priority priority;

        void start() {
            if (status == RequestStatus::Waiting) {
                status = RequestStatus::InProgress;
                return;
            }
        }

        void finish() {
            status = RequestStatus::Done;
        }

        void print() const {
            std::cout << "Plate: " << plateNumber;
            std::cout << ", Problem: " << parseProblemTypeToChar(problem);
            std::cout << ", Status: " << (int)(status);
            std::cout << ", Priority: " << (int)(priority) << std::endl;
		}
    };

    struct ServiceCenter {
    private:
        Request requests[100];
        int requestCount = 0;

        void getSortedWaitingRequests(Request outRequests[100], int& outCount) const {
            outCount = 0;

            for (int i = 0; i < requestCount; i++) {
                if (requests[i].status == RequestStatus::Waiting) {
                    outRequests[outCount] = requests[i];
                    outCount++;
                }
            }

            for (int i = 0; i < outCount - 1; i++) {
                for (int j = 0; j < outCount - i - 1; j++) {
                    if ((int)(outRequests[j].priority) < (int)(outRequests[j + 1].priority)) {
                        Request temp = outRequests[j];
                        outRequests[j] = outRequests[j + 1];
                        outRequests[j + 1] = temp;
                    }
                }
            }
        }

    public:
        void addRequest(const Request& request) {
            if (requestCount < 100) {
                requests[requestCount] = request;
				requestCount++;
            }
        }

        void startRequest(const char plateNumber[10]) {
            for (int i = 0; i < requestCount; i++) {
                if (std::strcmp(plateNumber, requests[i].plateNumber) == 0) {
                    requests[i].start();
                    return;
                }
            }
        }

        void finishRequest(const char plateNumber[10]) {
            for (int i = 0; i < requestCount; i++) {
                if (std::strcmp(plateNumber, requests[i].plateNumber) == 0) {
                    requests[i].finish();
                    return;
                }
            }
        }

        void getRequestsByStatus(RequestStatus status) {
            for (int i = 0; i < requestCount; i++) {
                if (requests[i].status == status) {
                    requests[i].print();
                }
            }
		}

        void getRequestsByProblemType(ProblemType problemType) {
            for (int i = 0; i < requestCount; i++) {
                if (requests[i].problem == problemType) {
                    requests[i].print();
                }
            }
		}

        void getWaitingRequestsByPriority() const {
            Request tempRequests[100];
            int tempCount = 0;

            getSortedWaitingRequests(tempRequests, tempCount);

            for (int i = 0; i < tempCount; i++) {
                tempRequests[i].print();
            }
        }
    };
}

int main()
{
	using namespace Service;
    int n;
	std::cin >> n;

	ServiceCenter serviceCenter;

    for (int i = 0; i < n; i++)
    {
        Request request;
        std::cin >> request.plateNumber;

        char problemType;
        std::cin >> problemType;
        request.problem = parseCharToProblemType(problemType);
		
        int priority;
        std::cin >> priority;
        if (priority < 1 || priority > 5) {
			std::cout << "Invalid value." << std::endl;
            continue;
        }
        request.priority = (Priority)(priority);

		serviceCenter.addRequest(request);
	}

    std::cout << "\nWaiting requests:\n";
    serviceCenter.getWaitingRequestsByPriority();
}
