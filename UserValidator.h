#pragma once
#include"User.h"

class UserValidator
{
public:
	class Builder;

private:
	bool useMinNameLen;
	bool useMinPasswordLen;
	bool useMinAge;
	bool useMaxAge;
	bool useDigitPassword;
	bool useUpperCasePassword;

	size_t minNameLen;
	size_t minPasswordLen;
	int minAge;
	int maxAge;

	UserValidator(bool useMinNameLen, size_t minNameLen, bool useMinPasswordLen,
		size_t minPasswordLen, bool useMinAge, int minAge, bool useMaxAge, int maxAge,
		bool useDigitPassword, bool useUpperCasePassword);

public:
	bool operator()(const User& user) const;

	static Builder builder();
};

class UserValidator::Builder
{
private:
	bool useMinNameLen = false;
	bool useMinPasswordLen = false;
	bool useMinAge = false;
	bool useMaxAge = false;
	bool useDigitPassword = false;
	bool useUpperCasePassword = false;

	size_t minNameLen = 0;
	size_t minPasswordLen = 0;
	int minAge = 0;
	int maxAge = 0;

public:
	Builder();

	Builder(const Builder& other) = delete;
	Builder& operator=(const Builder& other) = delete;

	Builder& withMinNameLen(size_t minNameLen);
	Builder& withMinPasswordLen(size_t minPasswordLen);
	Builder& withMinAge(int minAge);
	Builder& withMaxAge(int maxAge);
	Builder& withDigitPassword();
	Builder& withUpperCasePassword();

	UserValidator build()const;
};

bool isDigit(char s);
bool isUpperCase(char s);