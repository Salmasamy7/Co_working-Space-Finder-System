#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include "User.h"
#include "Book.h"
#include "Transaction.h"
#include "AdvancedTrie.h"
#include "SocialGraph.h"
#include "Analytics.h"
#include <unordered_map>
#include <vector>

class LibrarySystem {
private:
    std::unordered_map<int, User> users;
    std::unordered_map<int, Book> books;
    std::vector<Transaction> transactions;
    AdvancedTrie trie;
    SocialGraph socialGraph;
    Analytics analytics;
    std::string usersFile, booksFile, transactionsFile, friendsFile;
    int nextTransID;

    void loadAllData();
    void saveAllData();
    void insertBookIntoTrie(const Book& b);
    std::unordered_map<int, double> userActivityMap();

public:
    LibrarySystem();
    ~LibrarySystem();

    void addUser(const std::string& name, const std::string& email, int age);
    void addBook(const std::string& title, const std::string& author, int year, const std::string& keywords);
    void borrowBook(int userID, int bookID);
    void returnBook(int userID, int bookID);
    void searchBooksByKeyword(const std::string& keyword);
    void recommendFriends(int userID);
    void addFriend(int userA, int userB);
    void shortestPathBetweenUsers(int from, int to);
    void displayTopPopularBooks(int k);
    void generateAnalyticsReport();
    void listAllUsers();
    void listAllBooks();
    void exportSystemStateToText();
};

#endif