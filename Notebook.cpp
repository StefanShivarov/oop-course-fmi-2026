#define _CRT_SECURE_NO_WARNINGS
#include "Notebook.h"
#include<cstring>

Notebook::Notebook():countPages(0)
{
	title = new char[1];
	title[0] = '\0';
}

Notebook::Notebook(const char* title, size_t countPages)
{
	setTitle(title);
	this->countPages = countPages;
	pages = new Page[countPages];
}

Notebook::~Notebook()
{
	free();
}

void Notebook::setTitle(const char* title)
{
	if (title == nullptr)
	{
		return;
	}

	delete[]this->title;
	this->title = new char[strlen(title) + 1];
	strcpy(this->title, title);
}


void Notebook::copyFrom(const Notebook& other)
{
    if (other.title != nullptr)
    {
        title = new char[strlen(other.title) + 1];
        strcpy(title, other.title);
    }
    else
    {
        title = new char[1];
        title[0] = '\0';
    }

    countPages = other.countPages;
    pages = new Page[countPages];

    for (size_t i = 0; i < countPages; i++)
    {
        pages[i] = other.pages[i];
    }
}

void Notebook::free()

{
	delete[]title;
	title = nullptr;

	delete[]pages;
	pages = nullptr;

	countPages = 0;
}

Notebook::Notebook(const Notebook& other)
{
	copyFrom(other);
}

Notebook& Notebook::operator=(const Notebook& other)
{
	if (this == &other)
	{
		return *this;
	}

	free();
	copyFrom(other);

	return *this;
}

void Notebook::markPageAsImportant(size_t index)
{
	if (index >= countPages)
	{
		return;
	}

	pages[index].setImportance(true);
}

void Notebook::addTextToPage(size_t index, const char* text)
{
	if (index >= countPages || text == nullptr)
	{
		return;
	}

	pages[index].appendText(text);
}

void Notebook::printNotebook()const
{
	std::println("Title: {}", title);
	for (size_t i = 0;i < countPages;i++)
	{
		pages[i].printPage();
	}
}