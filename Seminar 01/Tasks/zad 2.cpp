

#include <iostream>
#include <cstring>
using std::cin;
using std::cout;

namespace Cars
{
    namespace Constants
    {
        const int REG_NUM = 9;
        const int MAX_SIZE = 12;
    }
    using namespace Constants;


    enum class ProblemType
    {
        ENGINE, BRAKES, TIRES, GEARBOX, SUSPENSION, OTHER
    };

    enum class Status
    {
        WAITING, IN_PROGRESS, DONE
    };

    struct Car {
        int order;
        char reg[REG_NUM];
        ProblemType type;
        Status status;
        int emergencyLevel;
    };



    ProblemType parseProblemType(char c)
    {
        switch (c)
        {
        case 'E': return ProblemType::ENGINE;
        case 'B': return ProblemType::BRAKES;
        case 'T': return ProblemType::TIRES;
        case 'G': return ProblemType::GEARBOX;
        case 'S': return ProblemType::SUSPENSION;
        default:  return ProblemType::OTHER;
        }
    }

    const char* GetProblem(ProblemType type)
    {
        switch (type)
        {
        case ProblemType::ENGINE: return "ENGINE";
        case ProblemType::BRAKES: return "BRAKES";
        case ProblemType::TIRES: return "TIRES";
        case ProblemType::GEARBOX: return "GEARBOX";
        case ProblemType::SUSPENSION: return "SUSPENSION";
        default: return "OTHER";

        }
    }

    void ReadCar(Car& car, int index)
    {
        char c;
        cin >> car.reg >> c >> car.emergencyLevel;
        car.type = parseProblemType(c);
        car.status = Status::WAITING;
        car.order = index;
    }

    Status parseStatus(const char* str)
    {
        if (strcmp(str, "WAITING") == 0) return Status::WAITING;
        if (strcmp(str, "IN_PROGRESS") == 0) return Status::IN_PROGRESS;
        if (strcmp(str, "DONE") == 0) return Status::DONE;

        return Status::WAITING;
    }
    void print(const Car& car)
    {
        cout << car.reg << " " << GetProblem(car.type) << " "
            << "Urgency: " << car.emergencyLevel << " " << "Status: ";

        switch (car.status)
        {
        case Status::WAITING:     cout << "WAITING"; break;
        case Status::IN_PROGRESS: cout << "IN_PROGRESS"; break;
        case Status::DONE:        cout << "DONE"; break;
        }

        cout << '\n';
    }
    void filterByStatus(const Car* cars, int n, Status status)
    {
        for (int i = 0; i < n; i++)
        {
            if (cars[i].status == status)
            {
                print(cars[i]);
            }
        }
    }

    bool higherPriority(const Car& car1, const Car& car2)
    {
        if (car1.emergencyLevel != car2.emergencyLevel)
            return car1.emergencyLevel > car2.emergencyLevel;

        return car1.order < car2.order;
    }

    void swap(Car& c1, Car& c2)
    {
        Car t = c1;
        c1 = c2;
        c2 = t;
    }
    void filterByPriorety(Car* cars, int n)
    {
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (higherPriority(cars[j], cars[minIdx])) {
                    minIdx = j;
                }
            }
            if (i != minIdx) swap(cars[i], cars[minIdx]);
        }
    }


    void startWork(Car* cars, int n, const char* reg)
    {
        for (int i = 0; i < n; i++)
        {
            if (strcmp(cars[i].reg, reg) == 0 && cars[i].status == Status::WAITING)
            {
                cars[i].status = Status::IN_PROGRESS;
                return;
            }
        }
    }
    void finishWork(Car* cars, int n, const char* reg)
    {
        for (int i = 0; i < n; i++)
        {
            if (strcmp(cars[i].reg, reg) == 0 && cars[i].status == Status::IN_PROGRESS)
            {
                cars[i].status = Status::DONE;
                return;
            }
        }
    }

    

    void printWaiting(const Car* cars, int n)
    {
        Car* sorted = new Car[n];
        for (int i = 0; i < n; i++)
        {
            sorted[i] = cars[i];
        }

        filterByPriorety(sorted, n);

        for (int i = 0; i < n; i++)
        {
            if (sorted[i].status == Status::WAITING)
            {
                print(sorted[i]);
            }
        }

        delete[] sorted;
    }

    void filterByType(const Car* cars, int n, ProblemType type) {
        for (int i = 0; i < n; i++) {
            if (cars[i].type == type) {
                print(cars[i]);
            }
        }
    }
}
    

int main()
{
	using namespace Cars;
    int n;
    cin >> n;

    Car* cars = new Car[n];
    for (int i = 0; i < n; i++)
    {
        ReadCar(cars[i],i);
    }

    cout << "\nWAITING REQUESTS SORTED BY PRIORITY:\n";
    printWaiting(cars, n);

    char reg[REG_NUM];
    cout << "\nStart work for reg: ";
    cin >> reg;
    startWork(cars, n, reg);

    cout << "Finish work for reg: ";
    cin >> reg;
    finishWork(cars, n, reg);

    char statusStr[MAX_SIZE];
    cout << "\nEnter status (WAITING, IN_PROGRESS, DONE): ";
    cin >> statusStr;
    Status status = parseStatus(statusStr);

    cout << "\nAll requests with this status:\n";
    filterByStatus(cars, n, status);

    char typeChar;
    cout << "Enter type (E, B, T, G, S, O): ";
    cin >> typeChar;

    ProblemType type = parseProblemType(typeChar);

    cout << "\nAll problems of this type:\n";
    filterByType(cars, n, type);
    delete[] cars;
}

