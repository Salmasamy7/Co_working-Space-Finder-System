#ifndef SOCIAL_GRAPH_H
#define SOCIAL_GRAPH_H

#include <unordered_map>
#include <vector>
#include <string>

class SocialGraph {
private:
    std::unordered_map<int, std::vector<int>> adjList;
public:
    void addEdge(int userA, int userB);
    std::vector<int> getFriends(int userID);
    std::vector<int> shortestPath(int from, int to);
    std::vector<int> mutualFriends(int userA, int userB);
    int getDegree(int userID);
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
};

#endif