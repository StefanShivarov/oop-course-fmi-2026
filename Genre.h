#pragma once
enum class Type
{
	Action,
	Comedy,
	Drama,
	Horror,
	Romance,
	Other
};

class Genre
{
public:
	static const char* convertTypeToString(Type type) ;
	static const Type convertStringToType(const char* str) ;
};

