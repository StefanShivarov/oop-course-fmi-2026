#ifndef USERVALIDATOR_USER_H
#define USERVALIDATOR_USER_H


class User {
    char* username = nullptr;
    char* password = nullptr;
    int age = 0;
public:
    User(const char* username, const char* password, int age);
    User(const User& other);
    User& operator=(const User& other);
    ~User();
    [[nodiscard]] const char* getUsername() const;
    [[nodiscard]] const char* getPassword() const;
    [[nodiscard]] int getAge() const;

    class UserValidator;
    static UserValidator validator();
};



#endif //USERVALIDATOR_USER_H
