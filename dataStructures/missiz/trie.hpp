#pragma once
#include <memory>
#include <string_view>
#include <unordered_map>

template <typename CharT = char> class Trie {
  private:
    struct TrieNode {
        std::unordered_map<CharT, std::unique_ptr<TrieNode>> children;
        bool isEndOfWord = false;
    };

    std::unique_ptr<TrieNode> m_root;

    bool removeRecurse(TrieNode *curr, std::basic_string_view<CharT> word,
                       size_t depth) {
        if (!curr)
            return false;

        if (depth == word.size()) {
            if (!curr->isEndOfWord)
                return false;
            curr->isEndOfWord = false;
            return curr->children.empty();
        }

        CharT c = word[depth];
        auto it = curr->children.find(c);

        if (it != curr->children.end()) {
            bool canBeDeleted =
                removeRecurse(it->second.get(), word, depth + 1);
            if (canBeDeleted) {
                curr->children.erase(it);
                return !curr->isEndOfWord && curr->children.empty();
            }
        }

        return false;
    }

  public:
    Trie() : m_root(std::make_unique<TrieNode>()) {}

    void insert(std::basic_string_view<CharT> word) {
        TrieNode *curr = m_root.get();

        for (CharT c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                curr->children[c] = std::make_unique<TrieNode>();
            }
            curr = curr->children[c].get();
        }

        curr->isEndOfWord = true;
    }

    void remove(std::basic_string_view<CharT> word) {
        removeRecurse(m_root.get(), word, 0);
    }

    bool hasWord(std::basic_string_view<CharT> word) {
        TrieNode *curr = m_root.get();

        for (CharT c : word) {
            auto it = curr->children.find(c);
            if (it == curr->children.end())
                return false;
            curr = it->second.get();
        }

        return curr->isEndOfWord;
    }

    bool hasPrefix(std::basic_string_view<CharT> prefix) const {
        TrieNode *curr = m_root.get();
        for (CharT c : prefix) {
            auto it = curr->children.find(c);
            if (it == curr->children.end()) {
                return false;
            }
            curr = it->second.get();
        }
        return true;
    }
};
