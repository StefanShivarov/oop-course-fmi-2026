#pragma once
#include "Event.h"
#include "Registration.h"

namespace StrUtils {
    void deepCopyString(char*& dest, const char* src);
}

namespace EventUtils {
    const char* eventTypeToString(EventType type);
    const char* ticketTypeToString(TicketType type);
}
