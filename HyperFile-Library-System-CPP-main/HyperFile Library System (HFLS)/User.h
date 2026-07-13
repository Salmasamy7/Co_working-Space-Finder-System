#ifndef USER_H
#define USER_H

#include <vector>
#include <string>

class User {
private:
    int userID;
    std::string name;
    std::string email;
    int age;
    std::vector<int> borrowedBooks; // IDs of books borrowed
    std::vector<int> friends;       // IDs of friends

public:
    User();
    User(int id, const std::string& n, const std::string& e, int a);

    int getUserID() const;
    std::string getName() const;
    std::string getEmail() const;
    int getAge() const;
    std::vector<int> getBorrowedBooks() const;
    std::vector<int> getFriends() const;

    void addBorrowedBook(int bookID);
    void removeBorrowedBook(int bookID);
    void addFriend(int friendID);
    void removeFriend(int friendID);

    void display() const;
    std::string toString() const;
    static User fromString(const std::string& line);
};

#endif