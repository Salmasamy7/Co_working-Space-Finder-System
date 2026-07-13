# HyperFile Library System (HFLS) - Advanced Data Structure Project

## 📚 Description
This is an **advanced C++ project** that implements a complete Library Management System using multiple data structures, text file persistence, and social graph features.  
The system manages users, books, borrowing transactions, friend relationships, keyword search via Trie, analytics using heap/queue/stack, and social network shortest path.

## 🚀 Features
- **File-based storage**: 4 text files (`users.txt`, `books.txt`, `transactions.txt`, `friends.txt`)
- **Trie** for fast keyword search in book titles and keywords
- **Social Graph** (adjacency list) for friends management and shortest path (BFS)
- **Analytics Engine**:
  - Popular books using `priority_queue`
  - Notifications using `queue`
  - Action history using `stack`
  - User activity scores
- **Object-Oriented Design**: Separate `.h` and `.cpp` files for each class
- **Multi-file export**: Export entire system state to `system_export.txt`

## 🛠️ Requirements
- C++17 compatible compiler (g++, clang++, MSVC)
- Windows / Linux / macOS

## 📁 Project Structure