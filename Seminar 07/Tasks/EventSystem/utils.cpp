#include "utils.h"
#include <cstring>

void StrUtils::deepCopyString(char*& dest, const char* src) {
    if (!src) {
        strcpy(dest, "");
        return;
    }

    dest = new char[strlen(src) + 1];
    strcpy(dest, src);
}

const char* EventUtils::eventTypeToString(EventType type) {
    switch (type) {
        case EventType::SEMINAR:
            return "Seminar";
        case EventType::CONCERT:
            return "Concert";
        case EventType::SPORTS_EVENT:
            return "Sports event";
        case EventType::WORKSHOP:
            return "Workshop";
        default:
            return "Other";
    }
}

const char* EventUtils::ticketTypeToString(TicketType type) {
    switch (type) {
        case TicketType::JUNIOR:
            return "Junior";
        case TicketType::STANDARD:
            return "Standard";
        case TicketType::STUDENT:
            return "Student";
        case TicketType::VIP:
            return "Vip";
        default:
            return "Other";
    }
}
