#pragma once
#include<print>

class Page
{
private:
	char* text = nullptr;
	bool importance;

	void copyFrom(const Page& other);
	void free();

public:
	Page();

	Page(const char* text, bool importance);

	~Page();

	Page(const Page& other);

	Page& operator=(const Page& other);

	void setText(const char* text);

	void setImportance(bool value);

	void appendText(const char* newText);

	void printPage()const;
};

