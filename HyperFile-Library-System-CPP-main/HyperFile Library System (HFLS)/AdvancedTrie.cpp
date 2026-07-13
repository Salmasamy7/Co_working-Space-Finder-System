#define _CRT_SECURE_NO_WARNINGS
#include "AdvancedTrie.h"
#include "Book.h"
#include <cctype>
#include <sstream>
#include <algorithm>
#include <vector>

TrieNode::TrieNode() : isEnd(false) {}

AdvancedTrie::AdvancedTrie() {
    root = std::make_shared<TrieNode>();
}

void AdvancedTrie::insert(const std::string& word, int bookID) {
    auto node = root;
    for (char ch : word) {
        ch = std::tolower(ch);
        if (node->children.find(ch) == node->children.end()) {
            node->children[ch] = std::make_shared<TrieNode>();
        }
        node = node->children[ch];
        node->bookIDs.insert(bookID);
    }
    node->isEnd = true;
}

std::set<int> AdvancedTrie::search(const std::string& prefix) {
    auto node = root;
    for (char ch : prefix) {
        ch = std::tolower(ch);
        if (node->children.find(ch) == node->children.end()) {
            return {};
        }
        node = node->children[ch];
    }
    return node->bookIDs;
}

void AdvancedTrie::loadFromBooks(const std::vector<Book>& books) {
    for (const auto& book : books) {
        std::string kw = book.getKeywords();
        std::stringstream ss(kw);
        std::string word;
        while (std::getline(ss, word, ',')) {
            word.erase(std::remove_if(word.begin(), word.end(), ::isspace), word.end());
            if (!word.empty()) insert(word, book.getBookID());
        }
        std::string title = book.getTitle();
        std::stringstream tss(title);
        while (tss >> word) {
            insert(word, book.getBookID());
        }
    }
}