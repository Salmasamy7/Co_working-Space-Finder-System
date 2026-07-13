#ifndef ADVANCED_TRIE_H
#define ADVANCED_TRIE_H

#include <unordered_map>
#include <memory>
#include <set>
#include <string>
#include <vector>

class Book;

class TrieNode {
public:
    std::unordered_map<char, std::shared_ptr<TrieNode>> children;
    std::set<int> bookIDs;
    bool isEnd;
    TrieNode();
};

class AdvancedTrie {
private:
    std::shared_ptr<TrieNode> root;
public:
    AdvancedTrie();
    void insert(const std::string& word, int bookID);
    std::set<int> search(const std::string& prefix);
    void loadFromBooks(const std::vector<Book>& books);
};

#endif