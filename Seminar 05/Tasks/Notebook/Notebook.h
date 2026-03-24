#pragma once
#include "Page.h"
class Notebook
{
private:
	
	const int BASIC_NUM_OF_PAGES = 10;

	Page* notebook = nullptr;
	int notebookPages;
	char* subject = nullptr;
	
	void copyFrom(const Notebook& other);
	void free();

public:
	Notebook();
	explicit Notebook(const char* subject);
	explicit Notebook(int numberOfPages);

	Notebook(const Notebook& other);
	Notebook& operator=(const Notebook& other);
	~Notebook();

	void markPageAsImportant(int index);
	void writeOnPage(const char* text, int index);
	const char* getSubject() const;
	const int getNumOfPages() const;
	void setSubject(const char* subject);
	void setNumberOfPages(const int number);
	void printNotebook();
};

