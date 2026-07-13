#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "LibrarySystem.h"

using namespace std;

int main() {
    cout << "=================================================\n";
    cout << "  ADVANCED DATA STRUCTURE LIBRARY SYSTEM v4.0\n";
    cout << "=================================================\n\n";

    LibrarySystem lib;

    // Adding demo data
    lib.addUser("Ahmed Ali", "ahmed@example.com", 25);
    lib.addUser("Sara Mohamed", "sara@example.com", 22);
    lib.addUser("Khaled Hassan", "khaled@example.com", 30);
    lib.addUser("Nourhan Tarek", "nour@example.com", 27);

    lib.addBook("The C++ Programming Language", "Bjarne Stroustrup", 2013, "C++,programming,OO,advanced");
    lib.addBook("Effective Modern C++", "Scott Meyers", 2014, "C++,modern,effective");
    lib.addBook("Data Structures and Algorithms", "Thomas Cormen", 2009, "algorithms,data structures,CS");
    lib.addBook("Clean Code", "Robert Martin", 2008, "clean,code,software,craftsmanship");
    lib.addBook("Design Patterns", "Erich Gamma", 1994, "patterns,OOP,design");

    lib.addFriend(1001, 1002);
    lib.addFriend(1001, 1003);
    lib.addFriend(1002, 1004);

    lib.borrowBook(1001, 1001);
    lib.borrowBook(1002, 1002);
    lib.borrowBook(1001, 1004);
    lib.borrowBook(1003, 1003);

    lib.returnBook(1001, 1004);

    cout << "\n--- Search by keyword 'C++' ---\n";
    lib.searchBooksByKeyword("C++");

    cout << "\n--- Friend recommendations for user 1001 ---\n";
    lib.recommendFriends(1001);

    cout << "\n--- Shortest path between 1001 and 1004 ---\n";
    lib.shortestPathBetweenUsers(1001, 1004);

    cout << "\n--- Top popular books ---\n";
    lib.displayTopPopularBooks(3);

    cout << "\n--- Analytics Report ---\n";
    lib.generateAnalyticsReport();

    cout << "\n--- List all users ---\n";
    lib.listAllUsers();

    cout << "\n--- List all books ---\n";
    lib.listAllBooks();

    cout << "\n--- Exporting system state ---\n";
    lib.exportSystemStateToText();

    cout << "\n===== SYSTEM DEMO COMPLETED SUCCESSFULLY =====\n";

    return 0;
}