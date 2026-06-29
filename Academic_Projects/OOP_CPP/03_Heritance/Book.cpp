#include "Book.h"

Book::Book(int id, std::string t, std::string a)
{
    this->id = id;
    title = t;
    author = a;
}

Book::~Book()
{
}

int Book::getId() const
{
    return id;
}

std::string Book::getTitle() const
{
    return title;
}

std::string Book::getAuthor() const
{
    return author;
}

void Book::setTitle(std::string t)
{
    title = t;
}

void Book::setAuthor(std::string a)
{
    author = a;
}

std::string Book::displayInfo() const
{
    return "ID: " + std::to_string(id) +
           " | Title: " + title +
           " | Author: " + author;
}