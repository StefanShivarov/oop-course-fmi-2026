#pragma once

class Page
{
private:
	char* information = nullptr;
	bool isImportant = false;


	void copyFromPage(const Page& other);
	void freePage();

public:
	Page();
	explicit Page(const char* text);
	Page(const Page& other);
	Page& operator=(const Page& other);
	~Page();

	void setText(const char* text);
	void appendInfo(const char* text);
	bool IsPageImprotant();
	void setImportance();
	void printDetails() ;
};

