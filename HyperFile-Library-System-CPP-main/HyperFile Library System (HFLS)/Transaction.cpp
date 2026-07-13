#define _CRT_SECURE_NO_WARNINGS
#include "Transaction.h"
#include <sstream>
#include <vector>

Transaction::Transaction() : transID(0), userID(0), bookID(0), returned(false) {}

Transaction::Transaction(int tid, int uid, int bid, const std::string& bdate)
    : transID(tid), userID(uid), bookID(bid), borrowDate(bdate), returned(false) {}

int Transaction::getTransID() const { return transID; }
int Transaction::getUserID() const { return userID; }
int Transaction::getBookID() const { return bookID; }
std::string Transaction::getBorrowDate() const { return borrowDate; }
std::string Transaction::getReturnDate() const { return returnDate; }
bool Transaction::isReturned() const { return returned; }

void Transaction::setReturned(const std::string& rdate) {
    returned = true;
    returnDate = rdate;
}

std::string Transaction::toString() const {
    return std::to_string(transID) + "|" + std::to_string(userID) + "|"
        + std::to_string(bookID) + "|" + borrowDate + "|"
        + (returned ? returnDate : "NOT_RETURNED") + "|" + (returned ? "1" : "0");
}

Transaction Transaction::fromString(const std::string& line) {
    std::stringstream ss(line);
    std::vector<std::string> parts;   // تم التصحيح
    std::string token;
    while (std::getline(ss, token, '|')) {
        parts.push_back(token);
    }
    if (parts.size() < 6) return Transaction();
    int tid = std::stoi(parts[0]);
    int uid = std::stoi(parts[1]);
    int bid = std::stoi(parts[2]);
    std::string bdate = parts[3];
    Transaction t(tid, uid, bid, bdate);
    if (parts[5] == "1") {
        t.setReturned(parts[4]);
    }
    return t;
}