#define _CRT_SECURE_NO_WARNINGS
#include "Page.h"
#include<cstring>

Page::Page() :importance(false)
{
	text = new char[1];
	text[0] = '\0';
}

Page::Page(const char* text, bool importance)
{
	setText(text);
	setImportance(importance);
}

Page::~Page()
{
	free();
}

void Page::copyFrom(const Page& other)
{
	if (other.text != nullptr)
	{
		text = new char[strlen(other.text) + 1];
		strcpy(text, other.text);
	}
	else
	{
		text = new char[1];
		text[0] = '\0';
	}

	importance = other.importance;
}

void Page::free()
{
	delete[]text;
	text = nullptr;
}

Page::Page(const Page& other)
{
	copyFrom(other);
}

Page& Page::operator=(const Page& other)
{
	if (this == &other)
	{
		return *this;
	}

	free();
	copyFrom(other);

	return *this;
}

void Page::setText(const char* text)
{
	if (text == nullptr)
	{
		return;
	}

	delete[]this->text;
	this->text = new char[strlen(text) + 1];
	strcpy(this->text, text);
}

void Page::setImportance(bool value)
{
	importance = value;
}

void Page::appendText(const char* newText)
{
	if (newText == nullptr)
	{
		return;
	}

	char* result = new char[strlen(text) + strlen(newText) + 1];

	strcpy(result, text);
	strcat(result, newText);

	free();
	text = result;
}

void Page::printPage()const
{
	if (importance)
	{
		std::println("Text: {}, Important page", text);
	}
	else
	{
		std::println("Text: {}",text);
	}
