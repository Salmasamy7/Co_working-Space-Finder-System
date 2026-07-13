#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>
#include <string>

class Analytics {
private:
    std::unordered_map<int, int> bookPopularity;
    std::unordered_map<int, double> userActivity;
    std::priority_queue<std::pair<int, int>> popularBooksHeap;
    std::queue<int> pendingNotifications;
    std::stack<std::vector<std::string>> actionHistory;
public:
    void updateBookBorrow(int bookID);
    std::vector<std::pair<int, int>> getTopPopularBooks(int k);
    void recordUserAction(int userID);
    double getUserActivity(int userID);
    void addNotification(int userID);
    void processNotifications();
    void pushHistory(const std::vector<std::string>& state);
    std::vector<std::string> popHistory();
    double calculateAverageBorrowsPerUser(const std::unordered_map<int, std::vector<int>>& userBorrows);
};

#endif