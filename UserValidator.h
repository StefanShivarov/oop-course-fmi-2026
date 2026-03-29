#pragma once
#include "User.h"

class UserValidator
{
public:
	class Builder;

private:
	bool hasMinUsernameLength;
	bool hasMinPasswordLength;
	bool hasMinAge;
	bool requiresDigit;
	bool requiresUppercase;

	int minUsernameLength;
	int minPasswordLength;
	int minAge;

	UserValidator(
		bool hasMinUsernameLength,
		int minUsernameLength,
		bool hasMinPasswordLength,
		int minPasswordLength,
		bool hasMinAge,
		int minAge,
		bool requiresDigit,
		bool requiresUppercase
	);

public:
	bool operator()(const User&) const;
	static Builder builder();
};

class UserValidator::Builder {
private:
	bool hasMinUsernameLength = false;
	bool hasMinPasswordLength = false;
	bool hasMinAge = false;
	bool requiresDigit = false;
	bool requiresUppercase = false;

	int minUsernameLength = 0;
	int minPasswordLength = 0;
	int minAge = 0;

public:

	Builder& setMinUsernameLength(int length);
	Builder& setMinPasswordLength(int length);
	Builder& setMinAge(int age);
	Builder& requireDigit();
	Builder& requireUppercase();

	UserValidator build()const;
};

