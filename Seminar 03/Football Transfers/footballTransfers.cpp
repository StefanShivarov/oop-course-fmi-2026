#include <iostream>
#include <cstring>
#include <print>
#include <format>

using std::cout;
using std::endl;
using std::println;

namespace utils {

    char* copyDynamicString(const char* src) {
        if (!src) {
            char* result = new char[1];
            result[0] = '\0';
            return result;
        }

        char* result = new char[strlen(src) + 1];
        strcpy(result, src);
        return result;
    }
}

// forward-declaration of a class, so that I can use it in Team
// definition is below Team, because Player itself has Team* as a member
class FootballPlayer;

class FootballClub {
private:
    char* name = nullptr;
    double budget;
    // ... other members like points, players, etc.
    // for example, we can have a collection of aggregated Players in the Team
    // Player** players; , but this is a bit more advanced

    // we can also make this an external utility function,
    // but since it's only used in this class, we can make it a private member function

public:
    FootballClub() : FootballClub("Unknown", 0.0) {}

    FootballClub(const char* name, double budget) : budget(budget) {
        this->name = utils::copyDynamicString(name);
    }

    ~FootballClub() {
        delete[] name; // important!
        // these below are optional
        name = nullptr;
        budget = 0.0;
    }

    const char* getName() const {
        return name;
    }

    double getBudget() const {
        return budget;
    }

    void setName(const char* newName) {
        delete[] name;
        name = utils::copyDynamicString(newName);
    }

    void setBudget(double newBudget) {
        if (newBudget < 0) {
            return;
        }
        budget = newBudget;
    }

    void print() const {
        println("Team: {}, budget: {:.2f}", name, budget);
    }

    // just declaring it as a member function, implementation is below the FootballPlayer class
    // so that it knows about its interface
    bool buyPlayer(FootballPlayer& player);
};

class FootballPlayer {
private:
    char* name = nullptr;
    int age = 0;
    int number = 0;
    double price = 0.0;
    FootballClub* team = nullptr; // aggregation: a FootballPlayer "uses/plays for" a Team, but does not own it, the Team can exist independently of the FootballPlayer

public:
    FootballPlayer() : FootballPlayer("Unknown", 0, 0, 0.0) {}

    FootballPlayer(const char* name, int age, int number, double price, FootballClub* team = nullptr) : team(team) {
        setAge(age);
        setNumber(number);
        setPrice(price);
        this->name = utils::copyDynamicString(name);
    }

    ~FootballPlayer() {
        delete[] name;
        name = nullptr;
        age = 0;
        number = 0;
        team = nullptr;
    }

    const char* getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    int getNumber() const {
        return number;
    }

    double getPrice() const {
        return price;
    }

    // non const getter so that we can increase the budget of the selling team in the buyPlayer function
    FootballClub* getTeam() {
        return team;
    }

    const FootballClub* getTeam() const {
        return team;
    }

    void setName(const char* newName) {
        if (!newName) {
            return;
        }
        delete[] name;
        name = utils::copyDynamicString(newName);
    }

    void setAge(int newAge) {
        if (newAge < 0) {
            return;
        }
        age = newAge;
    }

    void setNumber(int newNumber) {
        if (newNumber < 0) {
            return;
        }
        number = newNumber;
    }

    void setPrice(double newPrice) {
        if (newPrice < 0) {
            return;
        }
        price = newPrice;
    }

    void transferTo(FootballClub& newTeam) {
        if (team) {
            println("Transferring {} from {} to {}...", name, team->getName(), newTeam.getName());
        } else {
            println("{} is joining {} as a free agent...", name, newTeam.getName());
        }
        team = &newTeam;
    }

    void print() const {
        if (team) {
            println("Player: {}, age: {}, number: {}, price: {:.2f}, plays for: {}",
                    name, age, number, price, team->getName());
        } else {
            println("Player: {}, age: {}, number: {}, price: {:.2f}, free agent",
                    name, age, number, price);
        }
    }
};

bool FootballClub::buyPlayer(FootballPlayer& player) {
    if (this->budget < player.getPrice()) {
        return false;
    }

    if (player.getTeam() == this) {
        return false;
    }

    if (player.getTeam()) {
        this->budget -= player.getPrice();
        player.getTeam()->setBudget(player.getTeam()->getBudget() + player.getPrice());
    }
    player.transferTo(*this);
    return true;
}

int main() {
    FootballClub realMadrid("Real Madrid", 400000000.00);
    FootballClub manUnited("Manchester United", 340000000.00);
    FootballClub milan("Milan", 190000000.00);
    FootballClub banishoraFc("Banishora FC", 20.00);

    println("Teams are created first");
    realMadrid.print();
    manUnited.print();
    milan.print();
    banishoraFc.print();

    println();
    println("Players exist in an inner scope");
    {
        FootballPlayer mbappe("Kylian Mbappe", 26, 9, 200000000.00, &realMadrid);
        FootballPlayer bruno("Bruno Fernandes", 30, 8, 110000000.00, &manUnited);
        FootballPlayer leao("Rafael Leao", 25, 10, 90000000.00, &milan);
        FootballPlayer stefo("Stefan Shivarov Jr", 22, 24, 5.00, &manUnited);

        mbappe.print();
        bruno.print();
        leao.print();
        stefo.print();

        println();

        banishoraFc.buyPlayer(stefo); // transfer
        stefo.print();

        realMadrid.print();
        banishoraFc.print();
    } // the players are destroyed here, after that they no longer exist

    println();
    println("Players are already destroyed, but teams still exist");
    realMadrid.print();
    manUnited.print();
    milan.print();
    banishoraFc.print();

    // the next few lines showcase a problem with copying/assignment of objects with dynamic memory
    println();
    println("Broken copying/assignment example");

    FootballPlayer player("Stefo", 35, 7, 4.50, &banishoraFc);
    {
        // FootballPlayer emptyPlayer = player; // need to implement copy constructor for this to work properly
        FootballPlayer emptyPlayer;
        emptyPlayer = player; // need to implement operator= for this to work properly

    }// here the empty player's name is pointing to the same memory as the player above 's name
    // and right there that empty player's destructor will be called, and it will delete that same memory
    // so the original player will no longer point to a valid memory, and that is not good

    // we can fix that by implementing our own copy constructor/operator= for the FootballPlayer class,
    // but that will be discussed next week

    player.print(); // this should not work properly (the name will be weird)
}
