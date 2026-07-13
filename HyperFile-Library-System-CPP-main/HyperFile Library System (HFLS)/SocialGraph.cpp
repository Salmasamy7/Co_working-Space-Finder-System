#define _CRT_SECURE_NO_WARNINGS
#include "SocialGraph.h"
#include <fstream>
#include <sstream>
#include <queue>
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>

void SocialGraph::addEdge(int userA, int userB) {
    adjList[userA].push_back(userB);
    adjList[userB].push_back(userA);
}

std::vector<int> SocialGraph::getFriends(int userID) {
    if (adjList.find(userID) != adjList.end())
        return adjList[userID];
    return {};
}

std::vector<int> SocialGraph::shortestPath(int from, int to) {
    std::unordered_map<int, int> prev;
    std::queue<int> q;
    std::set<int> visited;
    q.push(from);
    visited.insert(from);
    prev[from] = -1;

    while (!q.empty()) {
        int curr = q.front(); q.pop();
        if (curr == to) break;
        for (int neighbor : adjList[curr]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                prev[neighbor] = curr;
                q.push(neighbor);
            }
        }
    }
    std::vector<int> path;
    if (prev.find(to) == prev.end()) return path;
    for (int at = to; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<int> SocialGraph::mutualFriends(int userA, int userB) {
    std::vector<int> fA = adjList[userA];
    std::vector<int> fB = adjList[userB];
    std::sort(fA.begin(), fA.end());
    std::sort(fB.begin(), fB.end());
    std::vector<int> mutual;
    std::set_intersection(fA.begin(), fA.end(), fB.begin(), fB.end(), std::back_inserter(mutual));
    return mutual;
}

int SocialGraph::getDegree(int userID) {
    return static_cast<int>(adjList[userID].size());
}

void SocialGraph::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        int u, v;
        char delim;
        ss >> u >> delim >> v;
        addEdge(u, v);
    }
}

void SocialGraph::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    std::set<std::pair<int, int>> edges;
    for (auto& [u, neighbors] : adjList) {
        for (int v : neighbors) {
            if (u < v) edges.insert({ u, v });
        }
    }
    for (auto& [u, v] : edges) {
        file << u << "|" << v << std::endl;
    }
}