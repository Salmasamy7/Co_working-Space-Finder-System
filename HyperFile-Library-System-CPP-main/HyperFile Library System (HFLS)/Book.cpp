#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

Book::Book() : bookID(0), year(0), available(true) {}

Book::Book(int id, const std::string& t, const std::string& a, int y, const std::string& kw)
    : bookID(id), title(t), author(a), year(y), keywords(kw), available(true) {}

int Book::getBookID() const { return bookID; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }
bool Book::isAvailable() const { return available; }
std::string Book::getKeywords() const { return keywords; }
void Book::setAvailable(bool flag) { available = flag; }

void Book::display() const {
    std::cout << "Book ID: " << bookID << ", Title: " << title << ", Author: " << author
        << ", Year: " << year << ", Available: " << (available ? "Yes" : "No")
        << ", Keywords: " << keywords << std::endl;
}

std::string Book::toString() const {
    return std::to_string(bookID) + "|" + title + "|" + author + "|" + std::to_string(year)
        + "|" + (available ? "1" : "0") + "|" + keywords;
}

Book Book::fromString(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> parts;   // تم التصحيح: تعريف parts قبل الاستخدام
    while (std::getline(ss, token, '|')) {
        parts.push_back(token);
    }
    if (parts.size() < 6) return Book();
    int id = std::stoi(parts[0]);
    std::string title = parts[1];
    std::string author = parts[2];
    int year = std::stoi(parts[3]);
    bool avail = (parts[4] == "1");
    std::string kw = parts[5];
    Book b(id, title, author, year, kw);
    b.setAvailable(avail);
    return b;
}