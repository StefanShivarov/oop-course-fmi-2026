#include <iostream>
#include <print>
#include <string>
using namespace std;
enum class type
{
    Engine,
    Brakes,
    Tires,
    Gearbox,
    Suspension,
    Other
};
enum class status
{
    Waiting,
    InProgress,
    Done
};
class RepairOrder
{
private:
    //urgency should be from 1 to 5
    int urgency;
    type problemType;
    status problemStatus;
    string plateNumber;

    type charToType(char c) const
    {
        switch (c)
        {
        case 'E':
            return type::Engine;
        case 'B':
            return type::Brakes;
        case 'T':
            return type::Tires;
        case 'G':
            return type::Gearbox;
        case 'S':
            return type::Suspension;
        case 'O':
            return type::Other;
        default:
            println("Issue converting char to problem type, defaulting to Other");
            return type::Other;
        }
    }
    char typeToChar() const
    {
        switch (problemType)
        {
        case type::Engine:
            return 'E';
        case type::Brakes:
            return 'B';
        case type::Tires:
            return 'T';
        case type::Gearbox:
            return 'G';
        case type::Suspension:
            return 'S';
        case type::Other:
            return 'O';
        }
    }
    string statusToString() const
    {
        switch (problemStatus)
        {
        case status::Waiting:
            return "Waiting";
        case status::InProgress:
            return "In Progress";
        case status::Done:
            return "Done";
        }
    }
public:
    void startOrder()
    {
        problemStatus = status::InProgress;
    }
    void finishOrder()
    {
        problemStatus = status::Done;
    }
    void printOrder() const
    {
        println("{} {} {}",urgency,typeToChar(), plateNumber);
    }
    string getStatusAsString() const
    {
        return statusToString();
    }
    string getRegistration()const
    {
        return plateNumber;
    }
    int getUrgency() const
    {
        return urgency;
    }
    char returnProblemTypeAsChar() const
    {
        return typeToChar();
    }
    RepairOrder(string unformattedOrder)
    {
        //format "{urgency} {type) {plateNumber}"
        problemStatus = status::Waiting;
        urgency = unformattedOrder[0] - '0';
        problemType = charToType(unformattedOrder[2]);
        plateNumber = unformattedOrder.substr(4);
    }
    RepairOrder()
    {
        //format "{urgency} {type) {plateNumber}"
        problemStatus = status::Waiting;
        urgency = 0;
        problemType = type::Other;
        plateNumber = "0";
    }
};

void swapOrders(RepairOrder& order1,RepairOrder& order2)
{
    RepairOrder temp = order1;
    order1 = order2;
    order2 = temp;
}
void FilterOrdersByStatus(const int n,const RepairOrder* orders)
{
    string statusWanted;
    getline(cin, statusWanted);
    for (int i = 0;i < n;i++)
    {
        if (statusWanted == orders[i].getStatusAsString())
        {
            orders[i].printOrder();
        }
    }
}
void startOrderByRegistration(const int n, RepairOrder* orders)
{
    string registration;
    getline(cin, registration);
    for (int i = 0;i < n;i++)
    {
        if (registration == orders[i].getRegistration())
        {
            orders[i].startOrder();
            break;
        }
    }
}
void finishOrderByRegistration(const int n, RepairOrder* orders)
{
    string registration;
    getline(cin, registration);
    for (int i = 0;i < n;i++)
    {
        if (registration == orders[i].getRegistration())
        {
            orders[i].finishOrder();
            break;
        }
    }
}
void printWaitingOrdersByUrgency(const int n, const RepairOrder* orders)
{
    int waitingCount = 0;
    for (int i = 0;i < n;i++)
    {
        if (orders[i].getStatusAsString() == "Waiting")
        {
            waitingCount++;
        }
    }
    RepairOrder* sortedOrders = new RepairOrder[waitingCount];
    int j = 0;
    for (int i = 0;i < n;i++)
    {
        if (orders[i].getStatusAsString() == "Waiting")
        {
            sortedOrders[j] = orders[i];
            j++;
        }
    }
    bool swapped;
    for (int i = 0;i < waitingCount - 1;i++)
    {
        swapped = false;
        for (int j = 0;j < waitingCount - i - 1;j++)
        {
            if (sortedOrders[j].getUrgency() < sortedOrders[j + 1].getUrgency())
            {
                swapOrders(sortedOrders[j],sortedOrders[j+1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
    for (int i = 0;i < waitingCount;i++)
    {
        sortedOrders[i].printOrder();
    }
    delete[] sortedOrders;
}
void filterOrdersByProblemType(const int n, const RepairOrder* orders)
{
    char c;
    cin >> c;
    cin.ignore();
    for (int i = 0;i < n;i++)
    {
        if (c == orders[i].returnProblemTypeAsChar())
        {
            orders[i].printOrder();
        }
    }
}
int main()
{
    int n;
    cin >> n;
    cin.ignore();
    RepairOrder* orders = new RepairOrder[n];
    for (int i = 0;i < n;i++)
    {
        string unformattedOrder;
        getline(cin, unformattedOrder);
        orders[i] = RepairOrder(unformattedOrder);
    }
    printWaitingOrdersByUrgency(n, orders);

    startOrderByRegistration(n, orders);

    finishOrderByRegistration(n, orders);

    FilterOrdersByStatus(n, orders);

    filterOrdersByProblemType(n, orders);

    delete[] orders;
}
