#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    int transID;
    int userID;
    int bookID;
    std::string borrowDate;
    std::string returnDate;
    bool returned;

public:
    Transaction();
    Transaction(int tid, int uid, int bid, const std::string& bdate);

    int getTransID() const;
    int getUserID() const;
    int getBookID() const;
    std::string getBorrowDate() const;
    std::string getReturnDate() const;
    bool isReturned() const;

    void setReturned(const std::string& rdate);
    std::string toString() const;
    static Transaction fromString(const std::string& line);
};

#endif