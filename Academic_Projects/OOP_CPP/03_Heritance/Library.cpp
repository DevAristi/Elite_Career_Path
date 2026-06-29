#include "Library.h"

Library::Library(std::string n)
{
    name = n;
}

Library::~Library()
{
    for (Book* book : books) {
        delete book;
    }
}

void Library::addBook(Book* b)
{
    books.push_back(b);
}

Book* Library::findBook(int id)
{
    for (Book* book : books) {
        if (book->getId() == id) {
            return book;
        }
    }
    return nullptr;
}

void Library::removeBook(int id) 
{
    for (auto it = books.begin(); it != books.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            books.erase(it);
            return;
        }
    }
}

std::string Library::displayBooks() const
{
    std::string result;
    result += "Library: " + name + "\n\n";
    for (Book* book : books) {
        result += book->displayInfo() + "\n";
    }
    if (books.empty()) {
        result += "No books registered.\n";
    }
    return result;
}