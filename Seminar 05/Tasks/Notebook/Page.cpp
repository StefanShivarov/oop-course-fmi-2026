#include "Page.h"
#include <cstring>
#include <iostream>
#pragma warning(disable:4996)
void Page::copyFromPage(const Page& other)
{
	if (other.information != nullptr)
	{
		information = new char[strlen(other.information) + 1];
		strcpy(information, other.information);
	}
	else
	{
		information = nullptr;
	}
	
	isImportant = other.isImportant;
}

void Page::freePage()
{
	delete[] information;
	information = nullptr;
	isImportant = false;
}

Page::Page() : information(nullptr)
{
}

Page::Page(const char* text) 
{
	setText(text);
}

Page::Page(const Page& other) : information(nullptr), isImportant(other.isImportant)
{
	copyFromPage(other);
}

Page& Page::operator=(const Page& other)
{
	if (this != &other)
	{
		freePage();
		copyFromPage(other);
	}

	return *this;
}

Page::~Page()
{
	freePage();
}

void Page::setText(const char* text)
{
	if (text == nullptr)
	{
		return;
	}
	delete[] information;
	information = new char[strlen(text) + 1];
	strcpy(information, text);
}

void Page::appendInfo(const char* text)
{
	if (information == text || text == nullptr)
	{
		return;
	}
	int currentLen = (information != nullptr) ? (strlen(information)) : (0);
	int extraLen = strlen(text);
	int totalLen = currentLen + extraLen;
	int spaceNeeded = (currentLen > 0) ? (1) : (0);

	char* newInfo = new char[totalLen + spaceNeeded + 1];
	if (information)
	{
		strcpy(newInfo, information);
		if (spaceNeeded > 0)
		{
			newInfo[currentLen] = ' ';
			newInfo[currentLen + 1] = '\0';
		}
	}
	else
	{
		newInfo[0] = '\0';
	}
	strcat(newInfo, text);

	delete[] information;
	information = newInfo;
}

bool Page::IsPageImprotant() 
{
	return (isImportant) ? true : false;
}

void Page::setImportance()
{
	isImportant = true;
}

void Page::printDetails()
{
	if (isImportant == true)
	{
		std::cout << "This page is of a great significance\n";
		std::cout << "This is the information on this page: " << information << std::endl;
		return;
	}
	std::cout << "This page is not important\n";
	std::cout << "This is the information on this page: " << information << std::endl;
}

