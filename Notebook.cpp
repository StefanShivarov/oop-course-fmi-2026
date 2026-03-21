#include "Notebook.h"
#include"Utils.h"
#include <cstring>
#include <print>

Notebook::Notebook()
{
	title = new char[1];
	title[0] = '\0';
}

Notebook::Notebook(const char* title, size_t count): count(count)
{
	this->title = utils::copyDynamicString(title);

	notebook = new Page[count];
}

void Notebook::copyFrom(const Notebook& other)
{
	title = utils::copyDynamicString(other.title);

	count = other.count;

	notebook = new Page[count];
	for (size_t i = 0; i < count; i++) {
		notebook[i] = other.notebook[i];
	}
}

void Notebook::free()
{
	delete[] title;
	delete[] notebook;
	title = nullptr;
	notebook = nullptr;
}

Notebook::Notebook(const Notebook& other)
{
	copyFrom(other);
}

Notebook& Notebook::operator=(const Notebook& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Notebook::~Notebook()
{
	free();
}

void Notebook::markAsImportant(size_t index)
{
	if (index >= count) {
		return;
	}
	notebook[index].setImportance(true);
}

void Notebook::addTextToPage(size_t index, const char* text)
{
	if (index >= count) {
		return;
	}
	notebook[index].appendText(text);
}

void Notebook::print() const
{
	std::println("Title: {}", title);
	for (size_t i = 0; i < count; i++)
	{
		std::println("Page {}: ", i);
		std::println("{}", notebook[i].getText());

		if (notebook[i].getImportance()) {
			std::println("[IMPORTANT]");
		}
			
	}
}
