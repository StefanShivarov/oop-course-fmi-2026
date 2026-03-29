#pragma once
#include"Page.h".

class Notebook
{
private:
	char* title = nullptr;
	Page* pages = nullptr;
	size_t countPages = 0;

	void copyFrom(const Notebook& other);
	void free();

public:
	Notebook();

	Notebook(const char* title, size_t countPages);

	~Notebook();

	Notebook& operator = (const Notebook& other);

	Notebook(const Notebook& other);

	void setTitle(const char* title);

	void markPageAsImportant(size_t index);

	void addTextToPage(size_t index, const char* text);

	void printNotebook()const;
};

