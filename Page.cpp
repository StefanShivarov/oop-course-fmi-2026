#include <iostream>
#include<cstring>
#include "Page.h"
#include "Utils.h"

Page::Page():isImportant(false)
{
	text = new char[1];
	text[0] = '\0';
}

Page::Page(const char* text, bool isImportant) : isImportant(isImportant)
{
	this->text = utils::copyDynamicString(text);
}

void Page::copyFrom(const Page& other)
{
	text = utils::copyDynamicString(other.text);
	isImportant = other.isImportant;
}

void Page::free()
{
	delete[] text;
	text = nullptr;
}

Page::Page(const Page& other)
{
	copyFrom(other);
}

Page& Page::operator=(const Page& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Page::~Page()
{
	free();
}

void Page::setImportance(bool value)
{
	isImportant = value;
}

void Page::appendText(const char* newText)
{
	if (!newText) {
		return; 
	}

	size_t newSize = strlen(text) + strlen(newText) + 1;

	char* result = new char[newSize];
	strcpy_s(result, newSize, text);
	strcat_s(result, newSize, newText);

	delete[] text;
	text = result;
}

const char* Page::getText() const
{
	return text;
}

bool Page::getImportance() const
{
	return isImportant;
}

