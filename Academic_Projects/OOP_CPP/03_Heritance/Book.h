#ifndef BOOK_H
#define BOOK_H
#include <string>

class Book {
private:
    int id;
    std::string title;
    std::string author;

public:
    Book(int id, std::string t, std::string a);
    ~Book();
    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    void setTitle(std::string t);
    void setAuthor(std::string a);
    std::string displayInfo() const;
};

#endif