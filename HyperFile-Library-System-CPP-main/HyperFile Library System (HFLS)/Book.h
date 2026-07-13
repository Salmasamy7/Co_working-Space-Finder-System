#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    int bookID;
    std::string title;
    std::string author;
    int year;
    bool available;
    std::string keywords; // comma separated

public:
    Book();
    Book(int id, const std::string& t, const std::string& a, int y, const std::string& kw);

    int getBookID() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
    bool isAvailable() const;
    std::string getKeywords() const;

    void setAvailable(bool flag);
    void display() const;
    std::string toString() const;
    static Book fromString(const std::string& line);
};

#endif