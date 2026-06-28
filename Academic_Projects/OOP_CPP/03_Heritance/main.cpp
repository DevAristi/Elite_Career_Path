#include <iostream>
#include "Library.h"
using namespace std;

int main() {
    string libraryName;
    cout << "Library Name: ";
    getline(cin, libraryName);
    Library library(libraryName);
    int option;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Add book\n";
        cout << "2. View books\n";
        cout << "3. Search book\n";
        cout << "4. Remove book\n";
        cout << "5. Exit\n";
        cout << "Option: ";
        cin >> option;

        switch(option) {
            case 1: {
                int id;
                string title, author;
                cout << "ID: ";
                cin >> id;
                cin.ignore();
                cout << "Title: ";
                getline(cin, title);
                cout << "Author: ";
                getline(cin, author);
                Book* newBook = new Book(id, title, author);
                library.addBook(newBook);
                cout << "Book added.\n";
                break;
            }

            case 2:
                cout << library.displayBooks();
                break;

            case 3: {
                int id;
                cout << "ID to search: ";
                cin >> id;
                Book* found = library.findBook(id);
                if (found != nullptr)
                    cout << found->displayInfo() << endl;
                else
                    cout << "Book not found.\n";
                break;
            }

            case 4: {
                int id;
                cout << "ID of the book to remove: ";
                cin >> id;
                Book* found = library.findBook(id);
                if (found != nullptr) {
                    library.removeBook(id);
                    cout << "Book successfully removed.\n";
                } else {
                    cout << "Error: No book found with that ID.\n";
                }
                break;
            }

            case 5:
                cout << "Program finished.\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while(option != 5);
    return 0;
}