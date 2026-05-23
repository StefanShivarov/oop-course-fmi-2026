#include <iostream>
#include <stdexcept>
#include <cassert>
#include <utility>
#include <string>

struct Counter
{
    unsigned useCount = 0;

    // This weak counter follows the common control-block idea:
    // weakCount = number of WeakPtr objects
    //           + 1 implicit weak reference while useCount > 0
    //
    // That means:
    // - when the last SharedPtr disappears, the managed object is destroyed
    // - the control block stays alive while weakCount > 0
    unsigned weakCount = 0;

    void addSharedPtr()
    {
        ++useCount;

        // When the first shared owner appears, we add the implicit weak ref.
        if (useCount == 1)
            ++weakCount;
    }

    void removeSharedPtr()
    {
        assert(useCount > 0);
        --useCount;

        // When the last shared owner disappears, the implicit weak ref is removed.
        if (useCount == 0)
        {
            assert(weakCount > 0);
            --weakCount;
        }
    }

    void addWeakPtr()
    {
        ++weakCount;
    }

    void removeWeakPtr()
    {
        assert(weakCount > 0);
        --weakCount;
    }
};

template <typename T>
class SharedPtr;

template <typename T>
class WeakPtr;

template <typename T>
class SharedPtr
{
    template <typename V>
    friend class WeakPtr;

private:
    T* data = nullptr;
    Counter* counter = nullptr;

private:
    void free()
    {
        if (!counter)
        {
            data = nullptr;
            return;
        }

        counter->removeSharedPtr();

        // When the strong count reaches 0, the managed object is destroyed.
        if (counter->useCount == 0)
        {
            delete data;
        }

        // The control block is destroyed only when weakCount also reaches 0.
        if (counter->weakCount == 0)
        {
            delete counter;
        }

        data = nullptr;
        counter = nullptr;
    }

    void copyFrom(const SharedPtr& other)
    {
        data = other.data;
        counter = other.counter;

        if (counter)
            counter->addSharedPtr();
    }

    void moveFrom(SharedPtr&& other) noexcept
    {
        data = other.data;
        counter = other.counter;

        other.data = nullptr;
        other.counter = nullptr;
    }

    // Private constructor used by WeakPtr::lock().
    // It succeeds only if the managed object is still alive.
    SharedPtr(const WeakPtr<T>& weak)
    {
        if (!weak.counter || weak.counter->useCount == 0)
        {
            data = nullptr;
            counter = nullptr;
            return;
        }

        data = weak.data;
        counter = weak.counter;
        counter->addSharedPtr();
    }

public:
    SharedPtr() = default;

    explicit SharedPtr(T* ptr) : data(ptr), counter(nullptr)
    {
        if (data)
        {
            counter = new Counter();
            counter->addSharedPtr();
        }
    }

    SharedPtr(const SharedPtr& other)
    {
        copyFrom(other);
    }

    SharedPtr& operator=(const SharedPtr& other)
    {
        if (this != &other)
        {
            free();
            copyFrom(other);
        }
        return *this;
    }

    SharedPtr(SharedPtr&& other) noexcept
    {
        moveFrom(std::move(other));
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept
    {
        if (this != &other)
        {
            free();
            moveFrom(std::move(other));
        }
        return *this;
    }

    ~SharedPtr()
    {
        free();
    }

    T& operator*()
    {
        if (!data)
            throw std::runtime_error("Dereferencing a null SharedPtr");
        return *data;
    }

    const T& operator*() const
    {
        if (!data)
            throw std::runtime_error("Dereferencing a null SharedPtr");
        return *data;
    }

    T* operator->()
    {
        if (!data)
            throw std::runtime_error("Accessing a null SharedPtr");
        return data;
    }

    const T* operator->() const
    {
        if (!data)
            throw std::runtime_error("Accessing a null SharedPtr");
        return data;
    }

    T* get() const
    {
        return data;
    }

    unsigned use_count() const
    {
        return counter ? counter->useCount : 0;
    }

    // Debug helper for learning purposes.
    // This is NOT the same as a standard library API.
    unsigned weak_count_debug() const
    {
        return counter ? counter->weakCount : 0;
    }

    void reset()
    {
        free();
    }

    explicit operator bool() const
    {
        return data != nullptr;
    }
};

template <typename T>
class WeakPtr
{
    template <typename V>
    friend class SharedPtr;

private:
    T* data = nullptr;
    Counter* counter = nullptr;

private:
    void free()
    {
        if (!counter)
        {
            data = nullptr;
            return;
        }

        counter->removeWeakPtr();

        // If no shared owners and no weak refs remain, destroy the control block.
        if (counter->weakCount == 0)
        {
            delete counter;
        }

        data = nullptr;
        counter = nullptr;
    }

    void copyFrom(const WeakPtr& other)
    {
        data = other.data;
        counter = other.counter;

        if (counter)
            counter->addWeakPtr();
    }

    void moveFrom(WeakPtr&& other) noexcept
    {
        data = other.data;
        counter = other.counter;

        other.data = nullptr;
        other.counter = nullptr;
    }

public:
    WeakPtr() = default;

    WeakPtr(const SharedPtr<T>& shared) : data(shared.data), counter(shared.counter)
    {
        if (counter)
            counter->addWeakPtr();
    }

    WeakPtr(const WeakPtr& other)
    {
        copyFrom(other);
    }

    WeakPtr& operator=(const WeakPtr& other)
    {
        if (this != &other)
        {
            free();
            copyFrom(other);
        }
        return *this;
    }

    WeakPtr(WeakPtr&& other) noexcept
    {
        moveFrom(std::move(other));
    }

    WeakPtr& operator=(WeakPtr&& other) noexcept
    {
        if (this != &other)
        {
            free();
            moveFrom(std::move(other));
        }
        return *this;
    }

    ~WeakPtr()
    {
        free();
    }

    // WeakPtr does not own the object.
    // It only checks whether there is still at least one SharedPtr owner.
    bool expired() const
    {
        return !counter || counter->useCount == 0;
    }

    // lock() returns a SharedPtr if the object is still alive,
    // otherwise it returns an empty SharedPtr.
    SharedPtr<T> lock() const
    {
        return SharedPtr<T>(*this);
    }

    unsigned use_count() const
    {
        return counter ? counter->useCount : 0;
    }

    // Debug helper for learning purposes.
    unsigned weak_count_debug() const
    {
        return counter ? counter->weakCount : 0;
    }
};

// ------------------------------------------------------------
// Demo
// ------------------------------------------------------------

struct User
{
    std::string name;

    User(std::string n) : name(std::move(n))
    {
        std::cout << "User created: " << name << '\n';
    }

    ~User()
    {
        std::cout << "User destroyed: " << name << '\n';
    }
};

int main()
{
    std::cout << std::boolalpha;

    SharedPtr<User> sp1(new User("Alice"));
    std::cout << "After creating sp1:\n";
    std::cout << "  sp1.use_count = " << sp1.use_count() << '\n';
    std::cout << "  sp1.weak_count_debug = " << sp1.weak_count_debug() << '\n';
    std::cout << '\n';

    WeakPtr<User> wp1(sp1);
    std::cout << "After creating wp1 from sp1:\n";
    std::cout << "  sp1.use_count = " << sp1.use_count() << '\n';
    std::cout << "  sp1.weak_count_debug = " << sp1.weak_count_debug() << '\n';
    std::cout << "  wp1.expired = " << wp1.expired() << '\n';
    std::cout << '\n';

    {
        SharedPtr<User> sp2 = sp1;
        std::cout << "After copying sp1 into sp2:\n";
        std::cout << "  sp1.use_count = " << sp1.use_count() << '\n';
        std::cout << "  sp2.use_count = " << sp2.use_count() << '\n';
        std::cout << "  wp1.use_count = " << wp1.use_count() << '\n';
        std::cout << '\n';
    }

    std::cout << "After sp2 goes out of scope:\n";
    std::cout << "  sp1.use_count = " << sp1.use_count() << '\n';
    std::cout << "  wp1.expired = " << wp1.expired() << '\n';
    std::cout << '\n';

    {
        SharedPtr<User> locked = wp1.lock();
        std::cout << "After wp1.lock():\n";
        std::cout << "  locked is valid = " << static_cast<bool>(locked) << '\n';
        std::cout << "  locked.use_count = " << locked.use_count() << '\n';

        if (locked)
        {
            std::cout << "  locked->name = " << locked->name << '\n';
        }
        std::cout << '\n';
    }

    std::cout << "Before resetting sp1:\n";
    std::cout << "  sp1.use_count = " << sp1.use_count() << '\n';
    std::cout << "  wp1.expired = " << wp1.expired() << '\n';
    std::cout << "  wp1.weak_count_debug = " << wp1.weak_count_debug() << '\n';
    std::cout << '\n';

    // This destroys the managed object because sp1 is the last SharedPtr owner.
    // The control block still remains alive because wp1 still exists.
    sp1.reset();

    std::cout << "After resetting sp1:\n";
    std::cout << "  wp1.expired = " << wp1.expired() << '\n';
    std::cout << "  wp1.use_count = " << wp1.use_count() << '\n';
    std::cout << "  wp1.weak_count_debug = " << wp1.weak_count_debug() << '\n';
    std::cout << '\n';

    SharedPtr<User> lockedAfterDestroy = wp1.lock();
    std::cout << "After lock() on expired weak pointer:\n";
    std::cout << "  lockedAfterDestroy is valid = " << static_cast<bool>(lockedAfterDestroy) << '\n';

    return 0;
}
