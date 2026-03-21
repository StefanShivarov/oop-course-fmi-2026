#pragma once

class Page
{
private:
	char* text = nullptr;
	bool isImportant;

public:
	Page();
	Page(const char*, bool);

	void copyFrom(const Page& other);
	void free();

	Page(const Page& other);
	Page & operator=(const Page & other);

	~Page();

	void setImportance(bool value);
	void appendText(const char* newText);

	const char* getText() const;
	bool getImportance() const;
};

