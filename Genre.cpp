#include "Genre.h"
#include<cstring>

const char* Genre::convertTypeToString(Type type) 
{
	switch (type)
	{
	case Type::Action: return "Action";
	case Type::Comedy: return "Comedy";
	case Type::Drama: return "Drama";
	case Type::Horror: return "Horror";
	case Type::Romance: return "Romance";
	default: return "Other";
	}
}

const Type Genre::convertStringToType(const char* str) 
{
	if (strcmp(str, "Action") == 0)
	{
		return Type::Action;
	}
	else if (strcmp(str, "Comedy") == 0)
	{
		return Type::Comedy;
	}
	else if (strcmp(str, "Drama") == 0)
	{
		return Type::Drama;
	}
	else if (strcmp(str, "Horror") == 0)
	{
		return Type::Horror;
	}
	else if (strcmp(str, "Romance") == 0)
	{
		return Type::Romance;
	}
	else
	{
		return Type::Other;
	}
}