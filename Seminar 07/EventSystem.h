#pragma once
#include "Registry.h"

class EventSystem
{
private:
    Registry** registries = nullptr;
    size_t count = 0;
    size_t capacity = 0;

    void resize();
    void copyFrom(const EventSystem& other);
    void moveFrom(EventSystem&& other) noexcept;
    void free();

public:
    EventSystem();
    EventSystem(const EventSystem& other);
    EventSystem& operator=(const EventSystem& other);
    EventSystem(EventSystem&& other) noexcept;
    EventSystem& operator=(EventSystem&& other) noexcept;
    ~EventSystem();

    void addRegistry(const Registry& reg);
    void removeRegistry(size_t index);
    const Registry* operator[](size_t index) const;
    size_t getCount() const;
};
