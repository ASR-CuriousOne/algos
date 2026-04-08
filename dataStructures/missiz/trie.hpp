#pragma once
#include <array>
#include <string>

struct TrieNode {
    std::array<TrieNode *, 26> children;
    char letter;
    bool isEndOfWord = false;

    TrieNode() : children{nullptr}, letter(0) {}
    TrieNode(char _letter) : children(), letter(_letter), isEndOfWord(false) {}
    TrieNode(char _letter, bool _isEndOfWord)
        : children(), letter(_letter), isEndOfWord(_isEndOfWord) {}

    ~TrieNode() {
        for (auto c : children) {
            if (c)
                delete c;
        }
    }
};

class Trie {
    const int wordEndCharIndex = 26;
    TrieNode *root;

    bool hasNoChildren(const TrieNode *node) {
        for (auto child : node->children) {
            if (child != nullptr)
                return false;
        }
        return true;
    }

    bool removeRecurse(TrieNode *curr, const std::string &word, int depth) {
        if (curr == nullptr) {
            return false;
        }

        if (depth == word.size()) {
            if (!curr->isEndOfWord) {
                return false;
            }

            curr->isEndOfWord = false;

            return hasNoChildren(curr);
        }

        char l = word[depth];

        if (!std::islower(l))
            return false;

        int index = l - 'a';

        bool canBeDeleted =
            removeRecurse(curr->children[index], word, depth + 1);

        if (canBeDeleted) {
            delete curr->children[index];

            curr->children[index] = nullptr;

            return !curr->isEndOfWord && hasNoChildren(curr);
        }
        return false;
    }

  public:
    Trie() { root = new TrieNode(); }
    Trie(const Trie &) = delete;
    Trie &operator=(const Trie &) = delete;

    void insert(const std::string &word) {
        TrieNode *curr = root;
        for (auto l : word) {
            if (!std::islower(l))
                continue;
            if (curr->children[l - 'a'] == nullptr) {
                curr->children[l - 'a'] = new TrieNode(l);
            }
            curr = curr->children[l - 'a'];
        }

        curr->isEndOfWord = true;
    }

    void remove(const std::string &word) { removeRecurse(root, word, 0); }

    bool hasWord(const std::string &word) {
        TrieNode *curr = root;

        for (auto l : word) {
            if (curr->children[l - 'a'] == nullptr) {
                return false;
            }
            curr = curr->children[l - 'a'];
        }

        return curr->isEndOfWord;
    }

    bool hasPrefix(const std::string &prefix) {
        TrieNode *curr = root;

        for (auto l : prefix) {
            if (curr->children[l - 'a'] == nullptr) {
                return false;
            }
            curr = curr->children[l - 'a'];
        }

        return true;
    }

    ~Trie() { delete root; }
};
