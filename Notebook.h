#pragma once
#include "Page.h"

class Notebook
{
private:
	char* title = nullptr;
	size_t count = 0;
	Page* notebook = nullptr;

public:
	Notebook();
	Notebook(const char*, size_t);

	void copyFrom(const Notebook& other);
	void free();

	Notebook(const Notebook& other);
	Notebook& operator=(const Notebook& other);

	~Notebook();

	void markAsImportant(size_t);

	void addTextToPage(size_t, const char*);

	void print()const;

};

