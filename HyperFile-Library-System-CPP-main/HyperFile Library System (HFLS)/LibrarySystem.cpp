#define _CRT_SECURE_NO_WARNINGS
#include "LibrarySystem.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <mutex>

using namespace std;

static mutex fileMutex;
static int globalID = 1000;

int generateID() {
    return ++globalID;
}

// ========== دالة الوقت الآمنة ==========
string getCurrentTime() {
    time_t now = time(nullptr);
    char buf[80];
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);   // بدل localtime غير الآمنة
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return string(buf);
}

LibrarySystem::LibrarySystem()
    : usersFile("users.txt"), booksFile("books.txt"),
    transactionsFile("transactions.txt"), friendsFile("friends.txt"), nextTransID(5000) {
    loadAllData();
}

LibrarySystem::~LibrarySystem() {
    saveAllData();
}

void LibrarySystem::loadAllData() {
    // Load Users
    ifstream ufile(usersFile);
    string line;
    while (getline(ufile, line)) {
        if (!line.empty()) {
            User u = User::fromString(line);
            users[u.getUserID()] = u;
        }
    }
    ufile.close();
    cout << "[LOAD] Loaded " << users.size() << " users.\n";

    // Load Books
    ifstream bfile(booksFile);
    while (getline(bfile, line)) {
        if (!line.empty()) {
            Book b = Book::fromString(line);
            books[b.getBookID()] = b;
        }
    }
    bfile.close();
    cout << "[LOAD] Loaded " << books.size() << " books.\n";

    // Load Transactions
    ifstream tfile(transactionsFile);
    while (getline(tfile, line)) {
        if (!line.empty()) {
            Transaction t = Transaction::fromString(line);
            transactions.push_back(t);
            if (t.getTransID() >= nextTransID) nextTransID = t.getTransID() + 1;
            analytics.updateBookBorrow(t.getBookID());
        }
    }
    tfile.close();
    cout << "[LOAD] Loaded " << transactions.size() << " transactions.\n";

    // Reconstruct social graph from users
    for (auto& [uid, user] : users) {
        for (int fid : user.getFriends()) {
            socialGraph.addEdge(uid, fid);
        }
    }
    socialGraph.loadFromFile(friendsFile);

    // Load Trie from books
    vector<Book> bookList;
    for (auto& [id, b] : books) bookList.push_back(b);
    trie.loadFromBooks(bookList);
}

void LibrarySystem::saveAllData() {
    lock_guard<mutex> lock(fileMutex);
    ofstream ufile(usersFile);
    for (auto& [id, user] : users) ufile << user.toString() << endl;
    ufile.close();

    ofstream bfile(booksFile);
    for (auto& [id, book] : books) bfile << book.toString() << endl;
    bfile.close();

    ofstream tfile(transactionsFile);
    for (auto& t : transactions) tfile << t.toString() << endl;
    tfile.close();

    socialGraph.saveToFile(friendsFile);
}

void LibrarySystem::insertBookIntoTrie(const Book& b) {
    string kw = b.getKeywords();
    stringstream ss(kw);
    string word;
    while (getline(ss, word, ',')) {
        word.erase(remove_if(word.begin(), word.end(), ::isspace), word.end());
        if (!word.empty()) trie.insert(word, b.getBookID());
    }
    string title = b.getTitle();
    stringstream tss(title);
    while (tss >> word) trie.insert(word, b.getBookID());
}

void LibrarySystem::addUser(const string& name, const string& email, int age) {
    int newID = generateID();
    User u(newID, name, email, age);
    users[newID] = u;
    cout << "User added with ID: " << newID << endl;
    analytics.recordUserAction(newID);
    saveAllData();
}

void LibrarySystem::addBook(const string& title, const string& author, int year, const string& keywords) {
    int newID = generateID();
    Book b(newID, title, author, year, keywords);
    books[newID] = b;
    insertBookIntoTrie(b);
    cout << "Book added with ID: " << newID << endl;
    saveAllData();
}

void LibrarySystem::borrowBook(int userID, int bookID) {
    if (users.find(userID) == users.end()) { cout << "User not found!\n"; return; }
    if (books.find(bookID) == books.end()) { cout << "Book not found!\n"; return; }
    if (!books[bookID].isAvailable()) { cout << "Book already borrowed!\n"; return; }
    if (users[userID].getBorrowedBooks().size() >= 3) {
        cout << "User has exceeded borrow limit (3 books).\n"; return;
    }
    books[bookID].setAvailable(false);
    users[userID].addBorrowedBook(bookID);
    Transaction t(nextTransID++, userID, bookID, getCurrentTime());
    transactions.push_back(t);
    analytics.updateBookBorrow(bookID);
    analytics.recordUserAction(userID);
    analytics.addNotification(userID);
    saveAllData();
    cout << "Book borrowed successfully.\n";
}

void LibrarySystem::returnBook(int userID, int bookID) {
    auto& user = users[userID];
    auto borrowed = user.getBorrowedBooks();
    if (find(borrowed.begin(), borrowed.end(), bookID) == borrowed.end()) {
        cout << "User did not borrow this book.\n"; return;
    }
    for (auto& t : transactions) {
        if (t.getUserID() == userID && t.getBookID() == bookID && !t.isReturned()) {
            t.setReturned(getCurrentTime());
            break;
        }
    }
    user.removeBorrowedBook(bookID);
    books[bookID].setAvailable(true);
    analytics.recordUserAction(userID);
    saveAllData();
    cout << "Book returned.\n";
}

void LibrarySystem::searchBooksByKeyword(const string& keyword) {
    set<int> ids = trie.search(keyword);
    if (ids.empty()) {
        cout << "No books found for keyword: " << keyword << endl;
        return;
    }
    cout << "Books containing keyword '" << keyword << "':\n";
    for (int id : ids) {
        if (books.find(id) != books.end()) books[id].display();
    }
}

void LibrarySystem::recommendFriends(int userID) {
    vector<int> friends = socialGraph.getFriends(userID);
    set<int> suggestions;
    for (int f : friends) {
        vector<int> fof = socialGraph.getFriends(f);
        for (int candidate : fof) {
            if (candidate != userID && find(friends.begin(), friends.end(), candidate) == friends.end()) {
                suggestions.insert(candidate);
            }
        }
    }
    cout << "Friend suggestions for user " << userID << ":\n";
    for (int s : suggestions) {
        if (users.find(s) != users.end())
            cout << "  - " << users[s].getName() << " (ID: " << s << ")\n";
    }
}

void LibrarySystem::addFriend(int userA, int userB) {
    if (users.find(userA) == users.end() || users.find(userB) == users.end()) {
        cout << "Invalid user ID.\n"; return;
    }
    socialGraph.addEdge(userA, userB);
    users[userA].addFriend(userB);
    users[userB].addFriend(userA);
    saveAllData();
    cout << "Friend connection added.\n";
}

void LibrarySystem::shortestPathBetweenUsers(int from, int to) {
    vector<int> path = socialGraph.shortestPath(from, to);
    if (path.empty()) cout << "No path found.\n";
    else {
        cout << "Shortest path: ";
        for (int p : path) cout << p << " ";
        cout << endl;
    }
}

void LibrarySystem::displayTopPopularBooks(int k) {
    auto top = analytics.getTopPopularBooks(k);
    cout << "Top " << k << " popular books:\n";
    for (auto& [bookID, count] : top) {
        if (books.find(bookID) != books.end())
            cout << "  - " << books[bookID].getTitle() << " (borrowed " << count << " times)\n";
    }
}

unordered_map<int, double> LibrarySystem::userActivityMap() {
    unordered_map<int, double> res;
    for (auto& [uid, user] : users)
        res[uid] = analytics.getUserActivity(uid);
    return res;
}

void LibrarySystem::generateAnalyticsReport() {
    cout << "\n========== ADVANCED ANALYTICS REPORT ==========\n";
    cout << "Total Users: " << users.size() << endl;
    cout << "Total Books: " << books.size() << endl;
    cout << "Total Transactions: " << transactions.size() << endl;

    unordered_map<int, vector<int>> userBorrows;
    for (auto& [uid, u] : users) userBorrows[uid] = u.getBorrowedBooks();
    double avgBorrow = analytics.calculateAverageBorrowsPerUser(userBorrows);
    cout << "Average books borrowed per user: " << avgBorrow << endl;

    int mostActiveUID = -1;
    double maxActivity = 0;
    for (const auto& [uid, act] : userActivityMap()) { // const auto& لتجنب مشكلة auto
        if (act > maxActivity) { maxActivity = act; mostActiveUID = uid; }
    }
    if (mostActiveUID != -1)
        cout << "Most active user: " << users[mostActiveUID].getName() << " (activity: " << maxActivity << ")\n";

    analytics.processNotifications();
    cout << "===============================================\n";
}

void LibrarySystem::listAllUsers() {
    for (auto& [id, u] : users) u.display();
}

void LibrarySystem::listAllBooks() {
    for (auto& [id, b] : books) b.display();
}

void LibrarySystem::exportSystemStateToText() {
    ofstream report("system_export.txt");
    report << "=== SYSTEM STATE EXPORT ===\n";
    report << "Generated: " << getCurrentTime() << "\n\n";
    report << "USERS:\n";
    for (auto& [id, u] : users) report << u.toString() << endl;
    report << "\nBOOKS:\n";
    for (auto& [id, b] : books) report << b.toString() << endl;
    report << "\nTRANSACTIONS:\n";
    for (auto& t : transactions) report << t.toString() << endl;
    report.close();
    cout << "System state exported to system_export.txt\n";
}