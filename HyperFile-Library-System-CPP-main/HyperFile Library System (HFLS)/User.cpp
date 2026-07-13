#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <vector>

User::User() : userID(0), age(0) {}

User::User(int id, const std::string& n, const std::string& e, int a)
    : userID(id), name(n), email(e), age(a) {}

int User::getUserID() const { return userID; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
int User::getAge() const { return age; }
std::vector<int> User::getBorrowedBooks() const { return borrowedBooks; }
std::vector<int> User::getFriends() const { return friends; }

void User::addBorrowedBook(int bookID) { borrowedBooks.push_back(bookID); }
void User::removeBorrowedBook(int bookID) {
    borrowedBooks.erase(std::remove(borrowedBooks.begin(), borrowedBooks.end(), bookID), borrowedBooks.end());
}
void User::addFriend(int friendID) { friends.push_back(friendID); }
void User::removeFriend(int friendID) {
    friends.erase(std::remove(friends.begin(), friends.end(), friendID), friends.end());
}

void User::display() const {
    std::cout << "User ID: " << userID << ", Name: " << name << ", Email: " << email << ", Age: " << age << std::endl;
    std::cout << "  Borrowed Books: ";
    for (int b : borrowedBooks) std::cout << b << " ";
    std::cout << std::endl;
    std::cout << "  Friends: ";
    for (int f : friends) std::cout << f << " ";
    std::cout << std::endl;
}

std::string User::toString() const {
    std::stringstream ss;
    ss << userID << "|" << name << "|" << email << "|" << age << "|";
    for (size_t i = 0; i < borrowedBooks.size(); ++i) {
        if (i > 0) ss << ",";
        ss << borrowedBooks[i];
    }
    ss << "|";
    for (size_t i = 0; i < friends.size(); ++i) {
        if (i > 0) ss << ",";
        ss << friends[i];
    }
    return ss.str();
}

User User::fromString(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(ss, token, '|')) {
        parts.push_back(token);
    }
    if (parts.size() < 5) return User();
    int id = std::stoi(parts[0]);
    std::string name = parts[1];
    std::string email = parts[2];
    int age = std::stoi(parts[3]);
    User u(id, name, email, age);
    // Borrowed books
    if (parts.size() > 4 && !parts[4].empty()) {
        std::stringstream bss(parts[4]);
        std::string bookID;
        while (std::getline(bss, bookID, ',')) {
            u.addBorrowedBook(std::stoi(bookID));
        }
    }
    // Friends
    if (parts.size() > 5 && !parts[5].empty()) {
        std::stringstream fss(parts[5]);
        std::string friendID;
        while (std::getline(fss, friendID, ',')) {
            u.addFriend(std::stoi(friendID));
        }
    }
    return u;
}