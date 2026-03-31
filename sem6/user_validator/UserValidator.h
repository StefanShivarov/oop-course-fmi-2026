#pragma once
#include "User.h"
class UserValidator {
public: 
	class Builder;

private:
	bool useMinNameLen;
	bool useMinPassLen;
	bool useMinAge;
	bool requireDigit;
	bool requireCapitalLetter;

	size_t minNameLen;
	size_t minPassLen;
	size_t minAge;

	UserValidator(
		bool useMinNameLen,
		size_t minNameLen,

		bool useMinPassLen,
		size_t minPassLen,

		bool useMinAge,
		size_t minAge,

		bool requireDigit,
		bool requireCapitalLetter
	);

public:
	bool operator()(const User& user) const;
	static Builder builder();

};

class UserValidator::Builder {
private: 
	bool useMinNameLen = false;
	size_t minNameLen = 0;

	bool useMinPassLen = false;
	size_t minPassLen = 0;

	bool useMinAge = false;
	size_t minAge = 0;

	bool requireDigit = false;
	bool requireCapitalLetter = false;

public:
	Builder() = default;
	Builder(const Builder& other) = delete;
	Builder& operator=(const Builder& other) = delete;
		 
	Builder& withMinNameLen(size_t len);
	Builder& withMinPassLength(size_t len);
	Builder& withMinAge(size_t age);

	Builder& withRequireDigit();
	Builder& withRequireCapitalLetter();

	UserValidator build() const;
};

