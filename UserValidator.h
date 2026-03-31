#pragma once
#include "User.h"

class UserValidator {
public:
	class Builder;

private:
	bool minUserLenght;
	bool minPassLenght;
	bool minAgeok;
	bool hasNumber;
	bool hasCapital;

	int minUsernameLenght;
	int minPasswordLenght;
	int minAge;
	bool needNumber;
	bool needCapital;

	void copyFrom(const UserValidator& other);
	void free();

	UserValidator(
		bool minUserLenght,
		int minUsernameLenght,
		bool minPassLenght,
		int minPasswordLenght,
		bool minAgeok,
		int minAge,
		bool hasNumber,
		bool needNumber,
		bool hasCapital,
		bool needCapital
	);

public:
	// the only constructor we have is private, meaning objects of this class can only be created via the builder

	UserValidator(const UserValidator& other);
	UserValidator& operator=(const UserValidator& other);
	~UserValidator();

	bool operator()(const User& user) const; // this allows the filter to act as a function

	static Builder builder(); // this static function returns a builder instance
	// it's a common practice when implementing builder pattern
};

class UserValidator::Builder {
private:
	bool minUserLenght = false;
	bool minPassLenght = false;
	bool minAgeok = false;
	bool hasNumber = false;
	bool hasCapital = false;

	int minUsernameLenght = 0;
	int minPasswordLenght = 0;
	int minAge = 0;
	bool needNumber = false;
	bool needCapital = false;

public:
	Builder();
	// we can forbid the copy operations for builders
	Builder(const Builder& other) = delete;
	Builder& operator=(const Builder& other) = delete;
	~Builder();

	Builder& withUsernameLeght(int minUsernameLenght);
	Builder& withPasswordLeght(int minPasswordLenght);
	Builder& withMinAge(int minAge);
	Builder& withNumber(bool needNumber);
	Builder& withCapital(bool needCapital);
	UserValidator build() const;
};