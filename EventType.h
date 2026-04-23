#pragma once

enum class Type
{
	SEMINAR,
	CONCERT,
	SPORT,
	PARTY,
	OTHER
};

class EventType
{
public:
	static const Type& convertToType(const char* type);
	static const char* convertToString(const Type& type);
};