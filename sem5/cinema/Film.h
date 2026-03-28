#pragma once
class Film
{
	char* title = nullptr;
	char* genre = nullptr;
	size_t duration = 0;
	double price = 0;

	void free();
	void copyFrom(const Film& other);

public:
	Film();
	Film(const Film& other);
	Film& operator=(const Film& other);
	~Film();

	Film(const char* title, const char* genre, size_t duration, double price);

	void printFilm() const;
};

