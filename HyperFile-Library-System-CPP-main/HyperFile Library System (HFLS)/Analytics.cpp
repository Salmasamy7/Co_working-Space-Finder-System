#define _CRT_SECURE_NO_WARNINGS
#include "Analytics.h"
#include <iostream>
#include <vector>

void Analytics::updateBookBorrow(int bookID) {
    bookPopularity[bookID]++;
    popularBooksHeap.push({ bookPopularity[bookID], bookID });
}

std::vector<std::pair<int, int>> Analytics::getTopPopularBooks(int k) {
    std::vector<std::pair<int, int>> result;
    auto tempHeap = popularBooksHeap;
    while (!tempHeap.empty() && result.size() < static_cast<size_t>(k)) {
        auto top = tempHeap.top(); tempHeap.pop();
        result.push_back({ top.second, top.first });
    }
    return result;
}

void Analytics::recordUserAction(int userID) {
    userActivity[userID] += 1.0;
}

double Analytics::getUserActivity(int userID) {
    auto it = userActivity.find(userID);
    if (it != userActivity.end()) return it->second;
    return 0.0;
}

void Analytics::addNotification(int userID) {
    pendingNotifications.push(userID);
}

void Analytics::processNotifications() {
    while (!pendingNotifications.empty()) {
        int uid = pendingNotifications.front(); pendingNotifications.pop();
        std::cout << "[NOTIFICATION] User " << uid << " has pending actions.\n";
    }
}

void Analytics::pushHistory(const std::vector<std::string>& state) {
    actionHistory.push(state);
}

std::vector<std::string> Analytics::popHistory() {
    if (actionHistory.empty()) return {};
    auto top = actionHistory.top();
    actionHistory.pop();
    return top;
}

double Analytics::calculateAverageBorrowsPerUser(const std::unordered_map<int, std::vector<int>>& userBorrows) {
    if (userBorrows.empty()) return 0;
    double sum = 0;
    for (auto& [uid, books] : userBorrows) {
        sum += static_cast<double>(books.size());
    }
    return sum / static_cast<double>(userBorrows.size());
}