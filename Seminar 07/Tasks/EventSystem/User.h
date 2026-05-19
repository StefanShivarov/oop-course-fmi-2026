#pragma once

class User {
public:
    User(const char* name, const char* email, unsigned age, double budget);

    User(const User& other);
    User& operator=(const User& other);

    User(User&& other) noexcept;
    User& operator=(User&& other) noexcept;

    ~User();

    const char* getName() const;
    const char* getEmail() const;
    unsigned getAge() const;
    double getBudget() const;

    void setName(const char* name);
    void setEmail(const char* email);
    void setAge(unsigned age);
    void setBudget(double budget);

    bool pay(double amount);

private:
    char* name = nullptr;
    char* email = nullptr;
    unsigned age = 0;
    double budget = 0.0;

    void free();
    void copyFrom(const User& other);
    void moveFrom(User&& other) noexcept;
};

void printUser(const User& user);
