#ifndef LIBRARY_H
#define LIBRARY_H
#include <vector>
#include <string>
#include "Book.h"

class Library {
private:
    std::string name;
    std::vector<Book*> books;

public:
    Library(std::string n);
    ~Library();
    void addBook(Book* b);
    Book* findBook(int id);
    void removeBook(int id);
    std::string displayBooks() const;
};

#endif