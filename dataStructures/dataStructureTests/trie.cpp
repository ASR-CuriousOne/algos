#include "missiz/trie.hpp"
#include <cassert>
#include <iostream>

// Tests written by Gemini (should probably put in some efforts myself).
int main() {
    Trie trie;

    std::cout << "Running Trie tests...\n";

    trie.insert("bat");
    trie.insert("bath");
    trie.insert("batman");
    trie.insert("apple");

    assert(trie.hasWord("bat") == true);
    assert(trie.hasWord("bath") == true);
    assert(trie.hasWord("batman") == true);
    assert(trie.hasWord("apple") == true);

    assert(trie.hasWord("ba") == false);
    assert(trie.hasWord("batm") == false);
    assert(trie.hasWord("apples") == false);
    std::cout << "[PASS] Basic Insertion and Search\n";

    assert(trie.hasPrefix("b") == true);
    assert(trie.hasPrefix("ba") == true);
    assert(trie.hasPrefix("bat") == true);
    assert(trie.hasPrefix("batm") == true);
    assert(trie.hasPrefix("app") == true);

    assert(trie.hasPrefix("cat") == false);
    assert(trie.hasPrefix("baths") == false);
    std::cout << "[PASS] Prefix Searching\n";

    trie.remove("bat");

    assert(trie.hasWord("bat") == false);
    assert(trie.hasWord("bath") == true);
    assert(trie.hasWord("batman") == true);
    assert(trie.hasPrefix("bat") == true);
    std::cout << "[PASS] Removal (Prefix Word)\n";

    trie.remove("bath");

    assert(trie.hasWord("bath") == false);
    assert(trie.hasWord("batman") == true);
    assert(trie.hasPrefix("bath") == false);
    assert(trie.hasPrefix("bat") == true);
    std::cout << "[PASS] Removal (Leaf Word / Pruning)\n";

    trie.remove("hello");
    trie.remove("apples");

    assert(trie.hasWord("apple") == true);
    std::cout << "[PASS] Removal (Non-existent words)\n";

    trie.insert("Cat");
    assert(trie.hasWord("at") == true);
    std::cout << "[PASS] Edge Cases (Invalid Chars Skipped)\n";

    return 0;
}
