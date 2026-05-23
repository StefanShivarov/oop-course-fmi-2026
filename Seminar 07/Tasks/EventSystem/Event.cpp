#include "Event.h"
#include "utils.h"
#include <utility>

using namespace StrUtils;

namespace {
    constexpr unsigned MAX_JUNIOR_AGE = 18;
    constexpr unsigned MAX_STUDENT_AGE = 23;

    constexpr double JUNIOR_DISCOUNT_MULTIPLIER = 0.6;
    constexpr double STUDENT_DISCOUNT_MULTIPLIER = 0.8;
}

Event::Event(const char* name,
             const char* description,
             EventType type,
             double baseParticipationPrice,
             size_t capacity)
    : type(type),
      baseParticipationPrice(baseParticipationPrice),
      capacity(capacity) {
    deepCopyString(this->name, name);
    deepCopyString(this->description, description);
    seats = new Registration*[capacity] { nullptr };
}

void Event::free() {
    for (size_t i = 0; i < capacity; i++) {
        delete seats[i];
    }

    delete[] seats;
    seats = nullptr;
    delete[] name;
    delete[] description;
    name = nullptr;
    description = nullptr;
}

void Event::copyFrom(const Event& other) {
    deepCopyString(name, other.name);
    deepCopyString(description, other.description);

    type = other.type;
    baseParticipationPrice = other.baseParticipationPrice;
    capacity = other.capacity;
    takenSeatsCount = other.takenSeatsCount;
    firstFreeSeatIndex = other.firstFreeSeatIndex;

    seats = new Registration*[capacity] { nullptr };

    for (size_t i = 0; i < capacity; i++) {
        if (other.seats[i]) {
            seats[i] = new Registration(*other.seats[i]);
        }
    }
}

void Event::moveFrom(Event&& other) noexcept {
    name = other.name;
    description = other.description;
    type = other.type;
    baseParticipationPrice = other.baseParticipationPrice;
    seats = other.seats;
    capacity = other.capacity;
    takenSeatsCount = other.takenSeatsCount;
    firstFreeSeatIndex = other.firstFreeSeatIndex;

    other.name = nullptr;
    other.description = nullptr;
    other.seats = nullptr;
    other.type = EventType::OTHER;
    other.baseParticipationPrice = 0.0;
    other.capacity = 0;
    other.takenSeatsCount = 0;
    other.firstFreeSeatIndex = 0;
}

Event::Event(const Event& other) {
    copyFrom(other);
}

Event& Event::operator=(const Event& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

Event::Event(Event&& other) noexcept {
    moveFrom(std::move(other));
}

Event& Event::operator=(Event&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

Event::~Event() {
    free();
}

const char* Event::getName() const {
    return name;
}

const char* Event::getDescription() const {
    return description;
}

EventType Event::getType() const {
    return type;
}

double Event::getBaseParticipationPrice() const {
    return baseParticipationPrice;
}

size_t Event::getCapacity() const {
    return capacity;
}

size_t Event::getTakenSeatsCount() const {
    return takenSeatsCount;
}

size_t Event::getFreeSeatsCount() const {
    return capacity - takenSeatsCount;
}

double Event::getCurrentRevenue() const {
    double result = 0.0;
    for (size_t i = 0; i < capacity; i++) {
        if (seats[i]) {
            result += seats[i]->getPaidPrice();
        }
    }
    return result;
}

double Event::calculatePriceForUser(const User& user, bool premiumTicket) const {
    if (premiumTicket) {
        return baseParticipationPrice * 2;
    }

    double price = baseParticipationPrice;

    // a better approach would be to make the multipliers
    // as class members instead of constants
    // so that they are different per event, but for simplicity i will keep it that way

    if (user.getAge() <= MAX_JUNIOR_AGE) {
        price *= JUNIOR_DISCOUNT_MULTIPLIER;
    } else if (user.getAge() <= MAX_STUDENT_AGE) {
        price *= STUDENT_DISCOUNT_MULTIPLIER;
    }
    return price;
}

TicketType Event::getTicketTypeForUser(const User& user, bool premiumTicket) {
    if (premiumTicket) {
        return TicketType::VIP;
    }

    if (user.getAge() <= MAX_JUNIOR_AGE) {
        return TicketType::JUNIOR;
    }

    if (user.getAge() <= MAX_STUDENT_AGE) {
        return TicketType::STUDENT;
    }

    return TicketType::STANDARD;
}

bool Event::addRegistration(Registration* reg, size_t seatIndex) {
    if (!reg || takenSeatsCount >= capacity || firstFreeSeatIndex >= capacity) {
        return false;
    }

    if (seatIndex >= capacity || seats[seatIndex]) {
        seatIndex = firstFreeSeatIndex;
    }

    seats[seatIndex] = reg;
    takenSeatsCount++;
    updateFirstFreeSeatIndex();
    return true;
}

bool Event::registerUser(User& user, bool premiumTicket) {
    return registerUserAtSeat(user, firstFreeSeatIndex, premiumTicket);
}

bool Event::registerUser(User* user, bool premiumTicket) {
    return registerUserAtSeat(user, firstFreeSeatIndex, premiumTicket);
}

bool Event::registerUserAtSeat(User& user, size_t seatIndex, bool premiumTicket) {
    if (takenSeatsCount >= capacity || firstFreeSeatIndex >= capacity) {
        return false;
    }

    double price = calculatePriceForUser(user, premiumTicket);
    if (user.getBudget() < price) {
        return false;
    }

    TicketType ticketType = getTicketTypeForUser(user, premiumTicket);

    if (!user.pay(price)) {
        return false;
    }

    return addRegistration(new Registration(user, price, ticketType), seatIndex);
}

bool Event::registerUserAtSeat(User* user, size_t seatIndex, bool premiumTicket) {
    return registerUserAtSeat(*user, seatIndex, premiumTicket);
}

bool Event::removeRegistration(size_t seatIndex) {
    if (seatIndex >= capacity || !seats[seatIndex]) {
        return false;
    }

    delete seats[seatIndex];
    seats[seatIndex] = nullptr;
    takenSeatsCount--;

    if (seatIndex < firstFreeSeatIndex) {
        firstFreeSeatIndex = seatIndex;
    }

    return true;
}

const Registration* Event::operator[](size_t index) const {
    if (index >= capacity) {
        return nullptr;
    }

    return seats[index];
}

void Event::updateFirstFreeSeatIndex() {
    for (size_t i = 0; i < capacity; i++) {
        if (!seats[i]) {
            firstFreeSeatIndex = i;
            return;
        }
    }

    firstFreeSeatIndex = capacity;
}

void printEvent(const Event& event) {
    std::cout << "=============================\n";
    std::cout << "Event: " << event.getName() << '\n';
    std::cout << "Description: " << event.getDescription() << '\n';
    std::cout << "Type: " << EventUtils::eventTypeToString(event.getType()) << '\n';
    std::cout << "Base participation price: " << event.getBaseParticipationPrice() << '\n';
    std::cout << "Capacity: " << event.getCapacity() << '\n';
    std::cout << "Taken seats: " << event.getTakenSeatsCount() << '\n';
    std::cout << "Free seats: " << event.getFreeSeatsCount() << '\n';
    std::cout << "Current revenue: " << event.getCurrentRevenue() << '\n';

    for (size_t i = 0; i < event.getCapacity(); i++) {
        const Registration* reg = event[i];

        std::cout << "Seat " << i << ": ";
        if (!reg) {
            std::cout << "[empty]\n";
            continue;
        }

        const User& user = reg->getUser();

        std::cout << user.getName()
                  << " | " << user.getEmail()
                  << " | paid: " << reg->getPaidPrice()
                  << " | ticket: " << EventUtils::ticketTypeToString(reg->getTicketType())
                  << '\n';
    }

    std::cout << "=============================\n";
}
