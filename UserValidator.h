#pragma once
#include "User.h"
#include <cstring>
#pragma warning (disable: 4996)

class UserValidator {
public:
	class Builder;
	bool operator()(const User& user);
private:
	bool usesMinNameLength;
	unsigned minNameLength;
	bool usesMinPasswordLength;
	unsigned minPasswordLength;
	bool usesMinAge;
	unsigned minAge;
	bool usesPasswordContainsDigit;
	bool usesPassswordContainsCapital;

	bool validateMinNameLength(const User& user) const;
	bool validateMinPasswordLength(const User& user) const;
	bool validateMinAge(const User& user) const;

	bool containsDigit(const char* str) const;
	bool containsUppercase(const char* str) const;

	bool validatePasswordContainsDigit(const User& user) const;
	bool validatePassswordContainsCapital(const User& user) const;

	UserValidator(
		bool usesMinNameLength,
		unsigned minNameLength,
		bool usesMinPasswordLength,
		unsigned minPasswordLength,
		bool usesMinAge,
		unsigned minAge,
		bool usesPasswordContainsDigit,
		bool usesPassswordContainsCapital
		);
};

class UserValidator::Builder {
private:
	bool usesMinNameLength = false;
	bool usesMinPasswordLength = false;
	bool usesMinAge = false;
	bool usesPasswordContainsDigit = false;
	bool usesPasswordContainsCapital = false;

	unsigned minNameLength = 0;
	unsigned minPasswordLength = 0;
	unsigned minAge = 0;

public:
	Builder() = default;

	Builder& withMinNameLength(unsigned minNameLength);
	Builder& withMinPasswordLength(unsigned minPasswordLength);
	Builder& withMinAge(unsigned minAge);
	Builder& withPasswordContainsDigit();
	Builder& withPasswordContainsCapital();

	UserValidator build() const;
};