#include"EventType.h"
#include<cstring>

const char* EventType::convertToString(const Type& type)
{
	switch (type)
	{
	case Type::SEMINAR:return "Seminar";
	case Type::CONCERT:return "Concert";
	case Type::PARTY:return "Party";
	case Type::SPORT:return "Sport event";
	default:return "Other";
	}
}

const Type& EventType::convertToType(const char* type)
{
	if (strcmp(type, "Seminar") == 0)
	{
		return Type::SEMINAR;
	}
	else if (strcmp(type, "Concert") == 0)
	{
		return Type::CONCERT;
	}
	else if (strcmp(type, "Party") == 0)
	{
		return Type::PARTY;
	}
	else if (strcmp(type, "Sport event") == 0)
	{
		return Type::SPORT;
	}
	else
	{
		return Type::OTHER;
	}
}