#define _CRT_SECURE_NO_WARNINGS
#include "UserValidator.h"
#include<cstring>

//UserValidator

UserValidator::UserValidator(bool useMinNameLen, size_t minNameLen, bool useMinPasswordLen,
	size_t minPasswordLen, bool useMinAge, int minAge, bool useMaxAge, int maxAge,
	bool useDigitPassword, bool useUpperCasePassword)
	:useMinNameLen(useMinNameLen), minNameLen(minNameLen), useMinPasswordLen(useMinPasswordLen),
	minPasswordLen(minPasswordLen), useMinAge(useMinAge), minAge(minAge), useMaxAge(useMaxAge),
	maxAge(maxAge), useDigitPassword(useDigitPassword), useUpperCasePassword(useUpperCasePassword){}

bool UserValidator::operator()(const User& user)const
{
	if (useMinNameLen && strlen(user.getUsername()) < minNameLen)
	{
		return false;
	}

	if (useMinPasswordLen && strlen(user.getPassword()) < minPasswordLen)
	{
		return false;
	}

	if (useMinAge && user.getAge() < minAge)
	{
		return false;
	}

	if (useMaxAge && user.getAge() > maxAge)
	{
		return false;
	}

	if (useDigitPassword)
	{
		bool hasDigit = false;
		const char* pass = user.getPassword();

		while (*pass != '\0')
		{
			if (isDigit(*pass))
			{
				hasDigit = true;
				break;
			}
			pass++;
		}

		if (!hasDigit)
		{
			return false;
		}
	}

	if (useUpperCasePassword)
	{
		bool hasUpperCase = false;
		const char* pass = user.getPassword();

		while (*pass != '\0')
		{
			if (isUpperCase(*pass))
			{
				hasUpperCase = true;
				break;
			}
			pass++;
		}

		if (!hasUpperCase)
		{
			return false;
		}
	}

	return true;
}

bool isDigit(char s)
{
	return (s >= '0' && s <= '9');
}

bool isUpperCase(char s)
{
	return (s >= 'A' && s <= 'Z');
}

UserValidator::Builder UserValidator::builder()
{
	return Builder();
}

UserValidator::Builder::Builder() = default;

//Builder

UserValidator::Builder& UserValidator::Builder::withMinNameLen(size_t minNameLen)
{
	useMinNameLen = true;
	this->minNameLen = minNameLen;
	return *this;
}

UserValidator::Builder& UserValidator::Builder::withMinPasswordLen(size_t minPasswordLen)
{
	useMinPasswordLen = true;
	this->minPasswordLen = minPasswordLen;
	return *this;
}

UserValidator::Builder& UserValidator::Builder::withMinAge(int minAge)
{
	useMinAge = true;
	this->minAge = minAge;
	return *this;
}

UserValidator::Builder& UserValidator::Builder::withMaxAge(int maxAge)
{
	useMaxAge = true;
	this->maxAge = maxAge;
	return *this;
}

UserValidator::Builder& UserValidator::Builder::withDigitPassword()
{
	useDigitPassword = true;
	return *this;
}

UserValidator::Builder& UserValidator::Builder::withUpperCasePassword()
{
	useUpperCasePassword = true;
	return *this;
}

UserValidator UserValidator::Builder::build()const
{
	return UserValidator(useMinNameLen, minNameLen, useMinPasswordLen, minPasswordLen,
		useMinAge, minAge, useMaxAge, maxAge, useDigitPassword, useUpperCasePassword);
}