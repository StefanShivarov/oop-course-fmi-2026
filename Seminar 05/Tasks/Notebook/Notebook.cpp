#include "Notebook.h"
#include <cstring>
#include <iostream>
#pragma warning(disable:4996)
void Notebook::copyFrom(const Notebook& other)
{
	if (other.subject )
	{
		subject = new char[strlen(other.subject) + 1];
		strcpy(subject, other.subject);
	}
	else
	{
		subject = nullptr;
	}

	this->notebookPages = other.notebookPages;
	if (other.notebook)
	{
		notebook = new Page[this->notebookPages];
		for (int i = 0; i < this->notebookPages; i++)
		{
			notebook[i] = other.notebook[i];
		}
	}
	else
	{
		notebook = nullptr;
	}
}

void Notebook::free()
{
	delete[] subject;
	delete[] notebook;

	subject = nullptr;
	notebook = nullptr;
	
	notebookPages = 0;
}

Notebook::Notebook() : subject(nullptr), notebookPages(BASIC_NUM_OF_PAGES)
{
	notebook = new Page[notebookPages];
}

Notebook::Notebook(const char* subject) : subject(nullptr), notebookPages(BASIC_NUM_OF_PAGES)
{
	setSubject(subject);
	notebook = new Page[notebookPages];
}

Notebook::Notebook(int numberOfPages) : subject(nullptr), notebookPages(BASIC_NUM_OF_PAGES)
{
	if (numberOfPages > 0)
	{
		notebookPages = numberOfPages;
		notebook = new Page[numberOfPages];
	}
	else
	{
		notebook = nullptr;
	}
}

Notebook::Notebook(const Notebook& other)
{
	copyFrom(other);
}

Notebook& Notebook::operator=(const Notebook& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Notebook::~Notebook()
{
	free();
}

void Notebook::markPageAsImportant(int index)
{
	if (index > 0 && index <= notebookPages)
	{
		notebook[index - 1].setImportance();
	}
}

void Notebook::writeOnPage(const char* text, int index)
{
	if (index > 0 && index <= notebookPages && notebook != nullptr)
	{
		notebook[index - 1].appendInfo(text);
	}
}


const char* Notebook::getSubject() const
{
	return subject;
}

const int Notebook::getNumOfPages() const
{
	return notebookPages;
}

void Notebook::setSubject(const char* subject)
{
	if (subject == nullptr)
	{
		return;
	}
	delete[] this->subject;
	this->subject = new char[strlen(subject) + 1];
	strcpy(this->subject, subject);
}

void Notebook::setNumberOfPages(const int numberOfPages)
{
	if (numberOfPages < 0 || numberOfPages > 200)
	{
		return;
	}
	Page* newNotebook = new Page[numberOfPages];
	if (this->notebook != nullptr)
	{
		int pagesToCopy = this->notebookPages < numberOfPages ? this->notebookPages : numberOfPages;
		for (int i = 0; i < pagesToCopy; i++)
		{
			newNotebook[i] = notebook[i];
		}
	}
	delete[] notebook;
	this->notebook = newNotebook;
	this->notebookPages = numberOfPages;
}

void Notebook::printNotebook()
{
	std::cout << "========== NOTEBOOK: " << (subject ? subject : "Untitled") << " ==========" << std::endl;
	std::cout << "Total pages: " << notebookPages << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	for (int i = 0; i < notebookPages; i++)
	{
		std::cout << "Page: " << i + 1 << ":" << std::endl;
		notebook[i].printDetails();
		std::cout << "-------------" << std::endl;
	}
}


